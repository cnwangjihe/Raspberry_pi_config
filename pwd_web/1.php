<!DOCTYPE html>
<html data-n-head-ssr data-n-head="">

<head>
    <meta data-n-head="true" charset="utf-8" />
    <meta data-n-head="true" name="viewport" content="width=device-width, initial-scale=1" />
    <meta data-n-head="true" data-hid="description" name="description" content="Nuxt.js project" />
    <title data-n-head="true">Password Generator</title>
    <link data-n-head="true" rel="icon" type="image/x-icon" href="/favicon.ico" />
    <link rel="stylesheet" type="text/css" href="css/full.css">
    <link rel="stylesheet" type="text/css" href="css/buttons.css">
    <link href="http://cdn.bootcss.com/font-awesome/4.2.0/css/font-awesome.min.css" rel="stylesheet">
    <script type="text/javascript" src="js/jquery.min.js"></script>
    <script type="text/javascript" src="js/buttons.js"></script>
    <style>
    body,
    html {
        margin: 0;
        padding: 0;
        color: #35495e;
        font-family: Microsoft YaHei, SimHei, Roboto Mono, Source Code Pro, Ubuntu Mono, Consolas
    }
    </style>
</head>

<body data-n-head="">
    <div data-server-rendered="true" id="__nuxt">
        <div class="progress" style="width:0%;height:2px;background-color:#3B8070;opacity:0;"></div>
        <div>
            <section class="container">
                <div class="card-wrap">
                    <div class="card cardIn">
                        <div class="title">
                            <div>Authentication 1</div>
                        </div>
                        <div class="question-content">
                            <!---->
                            <div class="question-text">
                                请输入「青山宪法」的内容
                            </div>
                            <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
                                <div class="question-input">
                                    <input value="" class="input">
                                </div>
                                    <br/>
                                <div>
                                    <input type="submit" value="Go" class="button button-pill button-primary">
                                </div>
                            </form>
                        </div>
                    </div>
                </div>
            </section>
        </div>
    </div>
</body>

</html>