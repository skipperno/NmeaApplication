var screenShown = false;


function preventEv(e) {
	if (e.preventDefault)
		e.preventDefault();
	else
		e.returnValue = false;
	return false;
}