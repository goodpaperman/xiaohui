function SB(pi_xObj,pi_bIsOver)
{
  pi_xObj.style.backgroundColor=(1==pi_bIsOver)?"#e0e0e0":"#eeeeee";
}

function FavSite()
{
  url = "http://www.xiaohui.com/?ref=fav";
  title = "小辉程序员之路 - XiaoHui.com";
  if (document.all)
    window.external.AddFavorite(url,title);
  else if (window.sidebar)
    window.sidebar.addPanel(title, url, "")
  else if(window.opera && window.print)
  { 
    var elem = document.createElement('a');
    elem.setAttribute('href',url);
    elem.setAttribute('title',title);
    elem.setAttribute('rel','sidebar');
    elem.click();
  }     
}

function AddFav()
{
  var t_strURL = encodeURIComponent(location.href);
  var t_strTitle = encodeURIComponent(document.title);
  var t_strFav = 
    "<p id=xh_fav_tag>收藏本文 : <br>\r\n" +
    "<table width=99% border=0><tr><td width=50%>"+
    "&raquo; <a href='http://digg.com/submit?phase=2&url="+t_strURL+"' target=_blank>[+] Digg</a>: Feature this article<br>\r\n" +
    "&raquo; <a href='http://del.icio.us/post?url="+t_strURL+"&title="+t_strTitle+"' target=_blank>[+] Del.icio.us</a>: Bookmark this article<br>\r\n" +
    "&raquo; <a href='http://www.furl.net/store?s=f&to=0&ti="+t_strURL+"&t="+t_strTitle+"' target=_blank>[+] Furl</a>: Bookmark this article<br>\r\n" + 
    "</td><td width=50%>"+
    "&raquo; <a href='http://www.google.com/bookmarks/mark?op=add&bkmk="+t_strURL+"&title="+t_strTitle+"' target=_blank>[+] Google 书签</a>: 收藏到 Google 书签<br>\r\n" +
    "&raquo; <a href='http://myweb.cn.yahoo.com/popadd.html?url="+t_strURL+"&title="+t_strTitle+"' target=_blank>[+] Yahoo 收藏</a>: 添加到 Yahoo 收藏 <br>\r\n" +
    "&raquo; <a href='http://shuqian.qq.com/post?title="+t_strTitle+"&uri="+t_strURL+"&jumpback=2&noui=1' target=_blank>[+] QQ 书签</a>: 添加到 QQ 书签 <br>\r\n" +
    "</td></tr></table></p>\r\n";
  document.write(t_strFav);
}

function AddFeed(pi_iCol)
{
  var t_strBreak = "&nbsp; &nbsp; ";
  if ( pi_iCol == 1 )
    t_strBreak = "<br />";
  var t_strFeed =
    "<div class=lmb><center>" +
    "<a href='http://www.zhuaxia.com/add_channel.php?url=http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-zhuaxia.gif' width='104' height='16' alt='Zhua Xia' id='noline_a'></a>\r\n" + t_strBreak + 
    "<a href='http://fusion.google.com/add?feedurl=http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-google.gif' width='104' height='16' alt='google reader' id='noline_a'></a>\r\n<br>" +
    "<a href='http://www.pageflakes.com/subscribe.aspx?url=http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-pageflakes.gif' width='104' height='16' lt='pageflakes' id='noline_a'></a>\r\n" + t_strBreak + 
    "<a href='http://www.rojo.com/add-subscription?resource=http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-rojo.gif' width='104' height='16' alt='Rojo' id='noline_a'></a>\r\n<br>" +
    "<a href='http://rss.gougou.com/sub/http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-gougou.gif' width='104' height='16' alt='Gougou' id='noline_a'></a>\r\n" + t_strBreak + 
    "<a href='http://www.bloglines.com/sub/http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-bloglines.gif' width='104' height='16' alt='bloglines' id='noline_a'></a>\r\n<br />" +
    "<a href='http://add.my.yahoo.com/rss?url=http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-yahoo.gif' width='104' height='16' lt='my yahoo' id='noline_a'></a>\r\n" + t_strBreak + 
    "<a href='http://www.newsgator.com/ngs/subscriber/subfext.aspx?url=http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-newsgator.gif' width='104' height='16' alt='newsgator' id='noline_a'></a>\r\n<br />" +
    "<a href='http://www.netvibes.com/subscribe.php?url=http://www.xiaohui.com/rss/' target='_blank' id='noline_a'><img border='0' src='/rss/rss-netvibes.gif' width='104' height='16' alt='netvibes' id='noline_a'></a>\r\n" + t_strBreak + 
    "<a href='http://www.xianguo.com/subscribe.php?url=http://www.xiaohui.com/rss/' target='_blank' id='noline_a'  ><img border='0' src='/rss/rss-xianguo.gif' width='104' height='16' alt='鲜果' id='noline_a'>\r\n</a><br />" +
    "</center></div>\r\n";
   document.write(t_strFeed);
}

function GetVar(pi_strURL, pi_strName)
{
  var t_strFind = "&"+pi_strName+"=";
  var t_iPos = pi_strURL.indexOf(t_strFind);
  
  if ( -1 == t_iPos )
  {
    t_strFind = "?"+pi_strName+"=";
    t_iPos = pi_strURL.indexOf(t_strFind);
  }
  if ( -1 == t_iPos )
    return "";
  t_strKey = pi_strURL.substring(t_iPos+t_strFind.length);
  t_iPos = t_strKey.indexOf("&");
  if ( t_iPos > 0 )
    t_strKey = t_strKey.substring(0,t_iPos);
  t_strKey = decodeURIComponent(t_strKey);
  return t_strKey;
}


function ShowWelcome()
{
   var t_strRef = document.referrer;
   //var t_strRef = "http://www.baidu.com/s?wd=%D1%F8%D6%ED%C5%E4%D6%D6";
   var t_strHttp = t_strRef.substring(0, 7);
   if ( "http://" == t_strHttp )
   {
     t_strRef = t_strRef.substring(7);
     var t_iPos = t_strRef.indexOf("/");
     if ( t_iPos > 0 )
     {
        var t_strURL = t_strRef.substring(0,t_iPos);
        t_iPos = t_strURL.indexOf("xiaohui.com");
        if ( t_iPos > -1 )
          return;
        var t_strKey = "";
        if ( t_strURL.indexOf("google.") > 0 )
          t_strKey = GetVar(t_strRef, "q");
        //else if ( t_strURL.indexOf("baidu.com") > 0 )
        //  t_strKey = GetVar(t_strRef, "wd");
        var t_strWelcome = "<div id=xh_welcome>　　您好, 来自 <b>"+ t_strURL + "</b> 的朋友! ";
        if ( "" != t_strKey )
          t_strWelcome = t_strWelcome + "您通过搜索 <font color=#ff000><b>" + t_strKey + "</b></font> 来到本站。";
        t_strWelcome = t_strWelcome + "<br>\r\n　　如果您是第一次来到本站, 欢迎<a href='#' onclick='FavSite()'>点此将本站添加至您的收藏夹</a>，或使用 <a href='http://www.xiaohui.com/rss/rss.htm' target=_blank>RSS FEED 订阅本站更新 <img src='/rss/rss.gif' border=0 width=16 height=16 align=absmiddle></a>，也可以<a href='http://www.xiaohui.com/about/maillist.htm' target=_blank>订阅本站邮件列表</a>，获取最新更新通知。<br></div>\r\n"
        document.write(t_strWelcome);
     }
   }
}