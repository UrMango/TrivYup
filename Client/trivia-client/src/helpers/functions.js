const htmlDecode = (input) => {
	var doc = new DOMParser().parseFromString(input, "text/html");
	return doc.documentElement.textContent;
}

export {
	htmlDecode
}