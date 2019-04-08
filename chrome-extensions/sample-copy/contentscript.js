
function copyToClipboard(str) {
	const el = document.createElement('textarea');
	el.value = str;
	document.body.appendChild(el);
	el.select();
	document.execCommand('copy');
	document.body.removeChild(el);
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
chrome.runtime.onMessage.addListener(function(message, sender, sendResponse) {
	var es = document.querySelectorAll("div#task-statement span.lang-ja div.part pre");	
	var samples = Array.from(es)
		.filter(x => x.id.substring(0,prefix.length)==prefix)
		.map(x => ({
			id: parseInt(x.id.substring(prefix.length)),
			text: x.innerText
		}));
	var parity = parityMap[message];
	var data = samples.filter(x => x.id%2==parity ).map(x => x.text);
	//console.log(data);
	const batchsample = message==="input"?formatInputSamples(data):formatOutputSamples(data);	
	copyToClipboard(batchsample);
//	alert(message+" successfully copied!\n"+data);
});
