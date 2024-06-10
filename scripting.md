<!doctype html>

<!--[if lt IE 7 ]> <html class="ie ie6 no-js" lang="en"> <![endif]-->
<!--[if IE 7 ]>    <html class="ie ie7 no-js" lang="en"> <![endif]-->
<!--[if IE 8 ]>    <html class="ie ie8 no-js" lang="en"> <![endif]-->
<!--[if IE 9 ]>    <html class="ie ie9 no-js" lang="en"> <![endif]-->
<!--[if gt IE 9]><!--><html class="no-js" lang="en"><!--<![endif]-->
<!-- the "no-js" class is for Modernizr. -->

<head id="frostbite" data-template-set="html5-reset">

    <meta charset="utf-8">

    <!-- Always force latest IE rendering engine (even in intranet) & Chrome Frame -->
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">

    <title>Scripting</title>

    <meta name="title" content="">
    <meta name="description" content="">
    <!-- Google will often use this as its description of your page/site. Make it good. -->

    <meta name="google-site-verification" content="">
    <!-- Speaking of Google, don't forget to set your site up: http://google.com/webmasters -->

    <!-- Dublin Core Metadata : http://dublincore.org/ -->
    <meta name="DC.title" content="Frostbite">
    <meta name="DC.subject" content="Dragonrealms MUD Frontend">
    <meta name="DC.creator" content="">

    <!--  Mobile Viewport Fix
     j.mp/mobileviewport & davidbcalhoun.com/2010/viewport-metatag
     device-width : Occupy full width of the screen in its current orientation
     initial-scale = 1.0 retains dimensions instead of zooming out if page height > device height
     maximum-scale = 1.0 retains dimensions instead of zooming in if page width < device width
     -->
    <!-- Uncomment to use; use thoughtfully!
     <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">
     -->

    <link rel="shortcut icon" href="img/favicon.png">
    <!-- This is the traditional favicon.
          - size: 16x16 or 32x32
          - transparency is OK
          - see wikipedia for info on browser support: http://mky.be/favicon/ -->

    <link rel="apple-touch-icon" href="img/favicon.png">
    <!-- The is the icon for iOS's Web Clip.
          - size: 57x57 for older iPhones, 72x72 for iPads, 114x114 for iPhone4's retina display (IMHO, just go ahead and use the biggest one)
          - To prevent iOS from applying its styles to the icon name it thusly: apple-touch-icon-precomposed.png
          - Transparency is not recommended (iOS will put a black BG behind the icon) -->

    <!-- CSS: screen, mobile & print are all in the same file -->
    <link rel="stylesheet" href="css/style.css">
    <link rel="stylesheet" href="css/web.css">

    <!-- all our JS is at the bottom of the page, except for Modernizr. -->
    <script src="js/modernizr-1.7.min.js"></script>
</head>

<body>

<div class="wrapper">
    <header>
        <hgroup>
            <img src="img/logo.png" /><br/>
            <h1>Frostbite</h1>
            <h2 class="">A frontend for Dragonrealms MUD</h2>
        </hgroup>
    </header>

    <h2 class="contents_head" id="contents">3 Scripting</h2>

    <div class="about">
        <p class="alert-box">
            The Frostbite client scripting support is provided by the <a href="http://www.ruby-lang.org/en/">Ruby</a>
            scripting engine and will therefore require the <a href="http://www.ruby-lang.org/en/">Ruby</a> runtime
            libraries to be <a href="installation.html">installed</a>.
        </p>
        <br/>
        <p>
            Ruby scripting engine adds a flexible and powerful scripting support for the game client. It is easy to use
            for beginners but still offers more complex scripting possibilities for advanced users.
        </p><br/>
        <h3>High level description</h3>
        <p>
            The scripting API is entirely written in Ruby and is located in the <i>"scripts/lib"</i> folder. A script is executed
            as a sub process of the frontend by calling the <i>"main.rb"</i> file in Ruby. All real time data for the Ruby process
            is provided over standard output (pipes) and on-demand data exchange is conducted over a custom TCP client->server solution.
        </p><p>
            The API Server opens a localhost socket on a random available port and stores it in the <i>"api.ini"</i> settings file.
            Using these stored settings the client is able to open up a socket connection to start a data sharing session which is
            based on a simple custom protocol. i.e "GET RT -> 0"
        </p>
        <p>
            The script flow from the frontend is as following:
        </p>
        <p>For example: <i>game client -> main.rb "braid.rb vines" -> runs -> braid.rb vines</i></p>
        <p>
            The scripting API includes:
        </p>
        <ul>
            <li>main.rb - general functions used by scripts;</li>
            <li>text.rb - functions for text matching;</li>
            <li>models.rb - wraps and handles API protocol queries;</li>
            <li>observer.rb - observer module, reacts to text events;</li>
            <li>roby_goto.rb - enables label based scripting.</li>
        </ul>
        <br/>
        <p>
            The scripting API functions are described in more detail in the <a href="api.html">API</a> section.
        </p>
    </div>

    <footer>
        <p><img class="git-hub-logo" src="img/GitHub-Mark-32px.png" /><small>https://github.com/matoom/frostbite</small></p>
    </footer>

</div>

<!-- here comes the javascript -->
<script src='js/jquery-1.5.1.min.js'></script>

<!-- this is where we put our custom functions -->
<script src="js/functions.js"></script>

<script type="text/javascript">

    var _gaq = _gaq || [];
    _gaq.push(['_setAccount', 'UA-36611098-1']);
    _gaq.push(['_trackPageview']);

    (function() {
        var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
        ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
        var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
    })();

</script>

</body>
</html>