jQuery.fn.populate=function(g,h){function parseJSON(a,b){b=b||'';if(a==undefined){}else if(a.constructor==Object){for(var c in a){var d=b+(b==''?c:'['+c+']');parseJSON(a[c],d)}}else if(a.constructor==Array){for(var i=0;i<a.length;i++){var e=h.useIndices?i:'';e=h.phpNaming?'['+e+']':e;var d=b+e;parseJSON(a[i],d)}}else{if(k[b]==undefined){k[b]=a}else if(k[b].constructor!=Array){k[b]=[k[b],a]}else{k[b].push(a)}}};function debug(a){if(window.console&&console.log){console.log(a)}}function getElementName(a){if(!h.phpNaming){a=a.replace(/\[\]$/,'')}return a}function populateElement(a,b,c){var d=h.identifier=='id'?'#'+b:'['+h.identifier+'="'+b+'"]';var e=jQuery(d,a);c=c.toString();c=c=='null'?'':c;e.html(c)}
function populateFormElement(a,b,c){
	var b=getElementName(b);var d=a[b];
if(d==undefined){d=jQuery('#'+b,a);if(d){d.html(c);return true}if(h.debug){debug('No such element as '+b)}return false}
if(h.debug){_populate.elements.push(d)}elements=d.type==undefined&&d.length?d:[d];
for(var e=0;e<elements.length;e++){
	var d=elements[e];if(!d||typeof d=='undefined'||typeof d=='function'){continue}
switch(d.type||d.tagName){
case'radio':d.checked=(d.value!=''&&c.toString()==d.value);
case'checkbox':var f=c.constructor==Array?c:[c];
for(var j=0;j<f.length;j++){d.checked|=d.value==f[j]}
break;
case'select-multiple':var f=c.constructor==Array?c:[c];for(var i=0;i<d.options.length;i++){for(var j=0;j<f.length;j++){d.options[i].selected|=d.options[i].value==f[j]}}break;
case'select':
	case'select-one':d.value=c.toString()||c;break;
	case'text':
		case'button':
		case'textarea':
		case'submit':
		default:c=c==null?'':c;d.value=c}
}
}
if(g===undefined){return this};var h=jQuery.extend({phpNaming:true,phpIndices:false,resetForm:true,identifier:'id',debug:false},h);if(h.phpIndices){h.phpNaming=true}var k=[];parseJSON(g);if(h.debug){_populate={arr:k,obj:g,elements:[]}}this.each(function(){var a=this.tagName.toLowerCase();
var b=a=='form'?populateFormElement:populateElement;
if(a=='form'&&h.resetForm){this.reset()}for(var i in k){b(this,i,k[i])}});return this};