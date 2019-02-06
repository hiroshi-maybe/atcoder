function copyinout(info, tab) {
	copyinput(info, tab);
	// without delay >250(ms), second one is not copied to clipboard..
	setTimeout(() => { copyoutput(info, tab); },750);
}
function copyinput(info, tab) {
	chrome.tabs.sendMessage(tab.id, "input");
}
function copyoutput(info, tab) {
	chrome.tabs.sendMessage(tab.id, "output");
}
chrome.contextMenus.create({"title": "Copy both","onclick": copyinout});
chrome.contextMenus.create({"title": "Copy input","onclick": copyinput});
chrome.contextMenus.create({"title": "Copy output","onclick": copyoutput});
