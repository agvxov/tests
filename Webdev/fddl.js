document.body.appendChild(
	Object.assign(document.createElement('div'),
					{style: 'position:fixed;bottom:0;left:0;',
					innerHTML:
`
<div style="background: purple; height: 200px; width: 300px;">
	<a id="myDownloader" style="color: white;" href="" download>myDownloader</a>
	<div>
		<input id="sharedClass" placeholder="shared class"></input>
	</div>
	<div>
		<input id="imageClass" placeholder="viewed image class"></input>
	</div>
	<div>
		<button id="caller">Execute</button>
	</div>
</div>
`
}));
function collectLinkOwners(myDownloader, sharedClass) {
	let r = [];
	for (i of document.getElementsByClassName(sharedClass)) {
		try {
			var linkOwner = i.getElementsByTagName("a")[0];
		} catch (err) {
			console.error("Missing 'a' subelement. However, this might be normal.");
		}
		r.push(linkOwner);
	}
	return r;
}
function download(myDownloader, imageClass, linkOwners) {
	var linkOwner = linkOwners.shift();
	linkOwner.click();
	requestAnimationFrame(async (myDownloader, imageClass, linkOwners) => {
		await new Promise(resolve => setTimeout(resolve, 5000));
		try {	// image
			myDownloader.href = document.getElementsByClassName(imageClass)[0].src;
		} catch (err) { // video
			let flag = false;
			for (i of document.getElementsByTagName('video')){
				if(i.offsetParent != null) {
					myDownloader.href = i.src;
					flag = true;
					break;
				}
			}
			if (!flag) {
				console.error("Missing media.");
			}
		}
		//myDownloader.click();
		console.log(myDownloader.href);
		download(myDownloader, imageClass, linkOwners);
	}, myDownloader, imageClass, linkOwners);
}
function execute() {
	const myDownloader = document.getElementById("myDownloader");
	const sharedClass  = document.getElementById("sharedClass").value;
	const imageClass   = document.getElementById("imageClass").value;

	if (sharedClass == "" || imageClass == "") {
		throw "Empty fields!";
	}

	download(myDownloader, imageClass, collectLinkOwners(myDownloader, sharedClass));
}
document.getElementById("caller").addEventListener("click", execute);
