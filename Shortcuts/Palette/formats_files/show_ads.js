
(function(){var g=null,h=(new Date).getTime();var i=this,aa=function(a,b){var c=a.split("."),d=i;!(c[0]in d)&&d.execScript&&d.execScript("var "+c[0]);for(var e;c.length&&(e=c.shift());)!c.length&&b!==void 0?d[e]=b:d=d[e]?d[e]:d[e]={}},ba=function(a,b,c){return a.call.apply(a.bind,arguments)},ca=function(a,b,c){var d=b||i;if(arguments.length>2){var e=Array.prototype.slice.call(arguments,2);return function(){var b=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(b,e);return a.apply(d,b)}}else return function(){return a.apply(d,
arguments)}},j=function(a,b,c){j=Function.prototype.bind&&Function.prototype.bind.toString().indexOf("native code")!=-1?ba:ca;return j.apply(g,arguments)};var ea=/&/g,fa=/</g,ga=/>/g,ha=/\"/g,k={"\0":"\\0","\u0008":"\\b","\u000c":"\\f","\n":"\\n","\r":"\\r","\t":"\\t","\u000b":"\\x0B",'"':'\\"',"\\":"\\\\"},n={"'":"\\'"},ja=function(a){for(var b=0,c=String(ia).replace(/^[\s\xa0]+|[\s\xa0]+$/g,"").split("."),a=String(a).replace(/^[\s\xa0]+|[\s\xa0]+$/g,"").split("."),d=Math.max(c.length,a.length),e=0;b==0&&e<d;e++){var f=c[e]||"",oa=a[e]||"",r=RegExp("(\\d*)(\\D*)","g"),l=RegExp("(\\d*)(\\D*)","g");do{var m=r.exec(f)||["","",""],o=l.exec(oa)||["","",
""];if(m[0].length==0&&o[0].length==0)break;b=q(m[1].length==0?0:parseInt(m[1],10),o[1].length==0?0:parseInt(o[1],10))||q(m[2].length==0,o[2].length==0)||q(m[2],o[2])}while(b==0)}return b},q=function(a,b){if(a<b)return-1;else if(a>b)return 1;return 0};var ka=document,s=window;var t=function(a){a=parseFloat(a);return isNaN(a)||a>1||a<0?0:a},w=function(a){return a=="true"?!0:a=="false"?!1:!1},la=/^([\w-]+\.)*([\w-]{2,})(\:[0-9]+)?$/,x=function(a){return!a?"pagead2.googlesyndication.com":(a=a.match(la))?a[0]:"pagead2.googlesyndication.com"};var ma=t("0"),na=t("0"),pa=t("0.2"),qa=t("0.02");var ra=w("false"),sa=w("false"),ta=w("false");var ua=function(){return x("")};var y,z,B,C,va=function(){return i.navigator?i.navigator.userAgent:g};C=B=z=y=!1;var D;if(D=va()){var wa=i.navigator;y=D.indexOf("Opera")==0;z=!y&&D.indexOf("MSIE")!=-1;B=!y&&D.indexOf("WebKit")!=-1;C=!y&&!B&&wa.product=="Gecko"}var E=z,F=C,xa=B,G;
a:{var H="",I;if(y&&i.opera)var J=i.opera.version,H=typeof J=="function"?J():J;else if(F?I=/rv\:([^\);]+)(\)|;)/:E?I=/MSIE\s+([^\);]+)(\)|;)/:xa&&(I=/WebKit\/(\S+)/),I)var ya=I.exec(va()),H=ya?ya[1]:"";if(E){var K,za=i.document;K=za?za.documentMode:void 0;if(K>parseFloat(H)){G=String(K);break a}}G=H}var ia=G,L={},Aa={},Ba=function(){return Aa[9]||(Aa[9]=E&&document.documentMode&&document.documentMode>=9)};!E||Ba();if(F||E)if(!E||!Ba())F&&(L["1.9.1"]||(L["1.9.1"]=ja("1.9.1")>=0));E&&(L["9"]||(L["9"]=ja("9")>=0));x("");var M=function(a){return!!a&&typeof a=="function"&&!!a.call},Ca=function(a,b){if(!(arguments.length<2))for(var c=1,d=arguments.length;c<d;++c)a.push(arguments[c])};function O(a){return typeof encodeURIComponent=="function"?encodeURIComponent(a):escape(a)}function Da(a,b){a.attachEvent?a.attachEvent("onload",b):a.addEventListener&&a.addEventListener("load",b,!1)}
function Ea(a,b){if(!(Math.random()<1.0E-4)){var c=Math.random();if(c<b)return a[Math.floor(c/b*a.length)]}return""};aa("google_protectAndRun",function(a,b,c){a=j(b,i,a);b=window.onerror;window.onerror=a;try{c()}catch(d){var c=d.toString(),e="";d.fileName&&(e=d.fileName);var f=-1;if(d.lineNumber)f=d.lineNumber;if(!a(c,e,f))throw d;}window.onerror=b});
aa("google_handleError",function(a,b,c,d){if(Math.random()<0.01)a=["http://",ua(),"/pagead/gen_204","?id=jserror","&jscb=",ra?1:0,"&jscd=",sa?1:0,"&context=",O(a),"&msg=",O(b),"&file=",O(c),"&line=",O(d.toString()),"&url=",O(ka.URL.substring(0,512)),"&ref=",O(ka.referrer.substring(0,512))],a.push(["&client=",O(s.google_ad_client),"&format=",O(s.google_ad_format),"&slotname=",O(s.google_ad_slot),"&output=",O(s.google_ad_output),"&ad_type=",O(s.google_ad_type)].join("")),a=a.join(""),s.google_image_requests||
(s.google_image_requests=[]),b=new Image,b.src=a,s.google_image_requests.push(b);return!ta});var Fa=function(a){try{var b=a.google_test;a.google_test=!b;if(a.google_test===!b)return a.google_test=b,!0}catch(c){}return!1},P=g,Ga=function(){if(!P){for(var a=window;a!=a.parent&&Fa(a.parent);)a=a.parent;P=a}return P};var Q,R=function(a){this.c=[];this.a=a||window;this.b=0;this.d=g},Ia=function(a,b){this.l=a;this.i=b};R.prototype.n=function(a,b){this.b==0&&this.c.length==0&&(!b||b==window)?(this.b=2,this.g(new Ia(a,window))):this.h(a,b)};R.prototype.h=function(a,b){this.c.push(new Ia(a,b||this.a));S(this)};R.prototype.o=function(a){this.b=1;if(a)this.d=this.a.setTimeout(j(this.f,this),a)};R.prototype.f=function(){if(this.b==1){if(this.d!=g)this.a.clearTimeout(this.d),this.d=g;this.b=0}S(this)};R.prototype.p=function(){return!0};
R.prototype.nq=R.prototype.n;R.prototype.nqa=R.prototype.h;R.prototype.al=R.prototype.o;R.prototype.rl=R.prototype.f;R.prototype.sz=R.prototype.p;var S=function(a){a.a.setTimeout(j(a.m,a),0)};R.prototype.m=function(){if(this.b==0&&this.c.length){var a=this.c.shift();this.b=2;a.i.setTimeout(j(this.g,this,a),0);S(this)}};R.prototype.g=function(a){this.b=0;a.l()};
var Ja=function(a){try{return a.sz()}catch(b){return!1}},Ka=function(a){return!!a&&(typeof a=="object"||typeof a=="function")&&Ja(a)&&M(a.nq)&&M(a.nqa)&&M(a.al)&&M(a.rl)},La=function(){if(Q&&Ja(Q))return Q;var a=Ga(),b=a.google_jobrunner;return Ka(b)?Q=b:a.google_jobrunner=Q=new R(a)},Ma=function(a,b){La().nq(a,b)},Na=function(a,b){La().nqa(a,b)};var Oa=/Chrome|Firefox|MSIE 8/,Pa=/MSIE [2-7]|PlayStation/i,Qa=/Android|Opera|Web Preview/,Ra=function(){var a=T,b=U.google_ad_width,c=U.google_ad_height,d=["<iframe"],e;for(e in a)a.hasOwnProperty(e)&&Ca(d,e+"="+a[e]);d.push('style="left:0;position:absolute;top:0;"');d.push("></iframe>");b="border:none;height:"+c+"px;margin:0;padding:0;position:relative;visibility:visible;width:"+b+"px";return['<ins style="display:inline-table;',b,'"><ins id="',a.id+"_anchor",'" style="display:block;',b,'">',d.join(" "),
"</ins></ins>"].join("")};var Sa=function(){},Ua=function(a,b,c){switch(typeof b){case "string":Ta(b,c);break;case "number":c.push(isFinite(b)&&!isNaN(b)?b:"null");break;case "boolean":c.push(b);break;case "undefined":c.push("null");break;case "object":if(b==g){c.push("null");break}if(b instanceof Array){var d=b.length;c.push("[");for(var e="",f=0;f<d;f++)c.push(e),Ua(a,b[f],c),e=",";c.push("]");break}c.push("{");d="";for(e in b)b.hasOwnProperty(e)&&(f=b[e],typeof f!="function"&&(c.push(d),Ta(e,c),c.push(":"),Ua(a,f,c),d=
","));c.push("}");break;case "function":break;default:throw Error("Unknown type: "+typeof b);}},Va={'"':'\\"',"\\":"\\\\","/":"\\/","\u0008":"\\b","\u000c":"\\f","\n":"\\n","\r":"\\r","\t":"\\t","\u000b":"\\u000b"},Wa=/\uffff/.test("\uffff")?/[\\\"\x00-\x1f\x7f-\uffff]/g:/[\\\"\x00-\x1f\x7f-\xff]/g,Ta=function(a,b){b.push('"');b.push(a.replace(Wa,function(a){if(a in Va)return Va[a];var b=a.charCodeAt(0),e="\\u";b<16?e+="000":b<256?e+="00":b<4096&&(e+="0");return Va[a]=e+b.toString(16)}));b.push('"')};var V=["google_ad_block","google_ad_channel","google_ad_client","google_ad_format","google_ad_height","google_ad_host","google_ad_host_channel","google_ad_host_tier_id","google_ad_output","google_ad_override","google_ad_region","google_ad_section","google_ad_slot","google_ad_type","google_ad_width","google_adtest","google_allow_expandable_ads","google_alternate_ad_url","google_alternate_color","google_analytics_domain_name","google_analytics_uacct","google_bid","google_city","google_color_bg","google_color_border",
"google_color_line","google_color_link","google_color_text","google_color_url","google_container_id","google_contents","google_country","google_cpm","google_ctr_threshold","google_cust_age","google_cust_ch","google_cust_gender","google_cust_id","google_cust_interests","google_cust_job","google_cust_l","google_cust_lh","google_cust_u_url","google_disable_video_autoplay","google_ed","google_eids","google_enable_osd","google_encoding","google_font_face","google_font_size","google_frame_id","google_gl",
"google_hints","google_image_size","google_kw","google_kw_type","google_language","google_max_num_ads","google_max_radlink_len","google_num_radlinks","google_num_radlinks_per_unit","google_num_slots_to_rotate","google_only_ads_with_video","google_only_pyv_ads","google_only_userchoice_ads","google_override_format","google_page_url","google_referrer_url","google_region","google_reuse_colors","google_rl_dest_url","google_rl_filtering","google_rl_mode","google_rt","google_safe","google_skip","google_tag_info",
"google_targeting","google_ui_features","google_ui_version","google_video_doc_id","google_video_product_type","google_with_pyv_ads"];var W=function(a){this.a=a;a.google_iframe_oncopy||(a.google_iframe_oncopy={handlers:{},log:[],img:Math.random()<0.01?[]:g});this.e=a.google_iframe_oncopy;a.setTimeout(j(this.k,this),3E4)},Xa;var X="var i=this.id,s=window.google_iframe_oncopy,H=s&&s.handlers,h=H&&H[i],w=this.contentWindow,d;try{d=w.document}catch(e){}if(h&&d&&(!d.body||!d.body.firstChild)){if(h.call){i+='.call';setTimeout(h,0)}else if(h.match){i+='.nav';w.location.replace(h)}s.log&&s.log.push(i)}";
/[&<>\"]/.test(X)&&(X.indexOf("&")!=-1&&(X=X.replace(ea,"&amp;")),X.indexOf("<")!=-1&&(X=X.replace(fa,"&lt;")),X.indexOf(">")!=-1&&(X=X.replace(ga,"&gt;")),X.indexOf('"')!=-1&&(X=X.replace(ha,"&quot;")));Xa=X;W.prototype.set=function(a,b){this.e.handlers[a]=b;this.a.addEventListener&&this.a.addEventListener("load",j(this.j,this,a),!1)};W.prototype.j=function(a){var a=this.a.document.getElementById(a),b=a.contentWindow.document;if(a.onload&&b&&(!b.body||!b.body.firstChild))a.onload()};
W.prototype.k=function(){if(this.e.img){var a=this.e.log,b=this.a.document;if(a.length)b=["http://",ua(),"/pagead/gen_204?id=iframecopy&log=",O(a.join("-")),"&url=",O(b.URL.substring(0,512)),"&ref=",O(b.referrer.substring(0,512))].join(""),a.length=0,a=new Image,this.e.img.push(a),a.src=b}};var Ya=function(){var a="script";return["<",a,' src="http://',x(""),'/pagead/js/r20110615/r20110616/show_ads_impl.js"></',a,">"].join("")},Za=function(a,b,c,d){return function(){var e=!1;d&&La().al(3E4);try{var f;try{f=!!a.document.getElementById(b).contentWindow.document}catch(oa){f=!1}if(f){var r=a.document.getElementById(b).contentWindow,
l=r.document;if(!l.body||!l.body.firstChild)l.open(),r.google_async_iframe_close=!0,l.write(c)}else{var m=a.document.getElementById(b).contentWindow,o;f=c;f=String(f);if(f.quote)o=f.quote();else{r=['"'];for(l=0;l<f.length;l++){var N=f.charAt(l),Ha=N.charCodeAt(0),qb=r,rb=l+1,da;if(!(da=k[N])){var A;if(Ha>31&&Ha<127)A=N;else{var p=N;if(p in n)A=n[p];else if(p in k)A=n[p]=k[p];else{var u=p,v=p.charCodeAt(0);if(v>31&&v<127)u=p;else{if(v<256){if(u="\\x",v<16||v>256)u+="0"}else u="\\u",v<4096&&(u+="0");
u+=v.toString(16).toUpperCase()}A=n[p]=u}}da=A}qb[rb]=da}r.push('"');o=r.join("")}m.location.replace("javascript:"+o)}e=!0}catch(xb){m=Ga().google_jobrunner,Ka(m)&&m.rl()}e&&(new W(a)).set(b,Za(a,b,c,!1))}},$a=function(){return ma&&na/ma||typeof window.google_hash_ratio=="number"&&window.google_hash_ratio||g};window.google_loader_used=!0;(function(a){if(!("google_onload_fired"in a))a.google_onload_fired=!1,Da(a,function(){a.google_onload_fired=!0})})(window);if(!window.google_loader_experiment)window.google_loader_experiment=Ea(["async_good_black","block_good_black"],pa)||Ea(["async_bad_black","block_bad_black"],qa)||"launch";var ab;a:{try{if(window.google_enable_async!==!0&&window.google_loader_experiment=="blockodd"&&window.top.location.hostname.length%2==1){ab=!1;break a}}catch(bb){}ab=!0}var cb;
if(cb=ab){var db;if(window.google_enable_async===!1)db=0;else{var eb=navigator.userAgent,fb=window.google_loader_experiment;db=(Pa.test(eb)?!1:Qa.test(eb)?fb=="async_bad_black":Oa.test(eb)?!0:fb=="async_good_black")&&!window.google_container_id&&(!window.google_ad_output||window.google_ad_output=="html")}cb=db}
if(cb){var gb=window;gb.google_unique_id?++gb.google_unique_id:gb.google_unique_id=1;for(var Y=window,_script$$inline_161="script",Z,U=Y,T={allowtransparency:'"true"',frameborder:'"0"',height:'"'+Y.google_ad_height+'"',hspace:'"0"',marginwidth:'"0"',marginheight:'"0"',onload:'"'+Xa+'"',scrolling:'"no"',vspace:'"0"',width:'"'+Y.google_ad_width+'"'},hb=U.document,$=T.id,ib=0;!$||U.document.getElementById($);)$="aswift_"+ib++;T.id=$;T.name=$;hb.write(Ra());Z=$;var jb;Y.google_page_url&&(Y.google_page_url=
String(Y.google_page_url));for(var kb=[],lb=0,mb=V.length;lb<mb;lb++){var nb=V[lb];if(Y[nb]!=g){var ob;try{var pb=[];Ua(new Sa,Y[nb],pb);ob=pb.join("")}catch(sb){}ob&&Ca(kb,nb,"=",ob,";")}}jb=kb.join("");for(var tb=0,ub=V.length;tb<ub;tb++)Y[V[tb]]=g;var vb=(new Date).getTime(),wb=$a(),yb=window.google_loader_experiment,zb=["<!doctype html><html><body><",_script$$inline_161,">",jb,"google_show_ads_impl=true;google_unique_id=",Y.google_unique_id,';google_async_iframe_id="',Z,'";google_start_time=',
h,";",wb?"google_hash_ratio="+wb+";":"",yb?'google_loader_experiment="'+yb+'";':"","google_bpp=",vb>h?vb-h:1,";</",_script$$inline_161,">",Ya(),"</body></html>"].join("");(Y.document.getElementById(Z)?Ma:Na)(Za(Y,Z,zb,!0))}else window.google_start_time=h,window.google_hash_ratio=$a(),document.write(Ya());})();