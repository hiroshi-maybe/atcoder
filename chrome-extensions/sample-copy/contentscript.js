
async function copyToClipboard(str) {
	try {
    	await navigator.clipboard.writeText(str);
	} catch (err) {
    	alert('Failed to copy: ', err);
	}

	return str;
}

function formatInputSamples(data) {
	var sep = "~\n";
	return data.join(sep)+sep;
}

function formatOutputSamples(data) {
	return data.join("");
}

const parityMap = {
	"input": 0,
	"output": 1
};
const prefix="pre-sample";
chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
	var es = document.querySelectorAll("div#task-statement span.lang-ja div.part pre");	
	var samples = Array.from(es)
		.filter(x => x.id.substring(0,prefix.length)==prefix)
		.map(x => ({
			id: parseInt(x.id.substring(prefix.length)),
			text: x.innerText
		}));
	var parity = parityMap[message];
	var data = samples.filter(x => x.id%2==parity ).map(x => x.text);
	const batchsample = message==="input"?formatInputSamples(data):formatOutputSamples(data);	
	
	(async () => {
		const data = await copyToClipboard(batchsample);
		console.log("Copied", data);
		sendResponse(data);
	})();
	return true;
});
