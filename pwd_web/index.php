<!DOCTYPE html>
<html data-n-head-ssr data-n-head="">

<head>
	<!-- Global site tag (gtag.js) - Google Analytics -->
	<script async src="https://www.googletagmanager.com/gtag/js?id=UA-XXXXXXXX"></script>
	<script>
		window.dataLayer = window.dataLayer || [];
		function gtag(){dataLayer.push(arguments);}
		gtag('js', new Date());

		gtag('config', 'UA-XXXXXXXX');
	</script>

	<meta data-n-head="true" charset="utf-8" />
	<meta data-n-head="true" name="viewport" content="width=device-width, initial-scale=1, user-scalable=0" />
	<meta data-n-head="true" data-hid="description" name="description" content="Nuxt.js project" />
	<title data-n-head="true">Password Generator</title>
	<link rel="stylesheet" type="text/css" href="css/full.min.css">
	<link rel="stylesheet" type="text/css" href="css/buttons.min.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
	<script
	src="https://code.jquery.com/jquery-3.3.1.min.js"
	integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
	crossorigin="anonymous"></script>
	<!-- <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script> -->
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
	<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
	<link href="http://cdn.bootcss.com/font-awesome/4.2.0/css/font-awesome.min.css" rel="stylesheet">
	<script type="text/javascript" src="js/buttons.js"></script>
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-select/1.13.2/css/bootstrap-select.min.css">
	<script src="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-select/1.13.2/js/bootstrap-select.min.js"></script>
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
<?php
require "settings.php";
session_start();

if (empty($_SESSION['token_auth']))
    $_SESSION['token_auth'] = bin2hex(random_bytes(32));

if (empty($_SESSION['token_calc']))
    $_SESSION['token_calc'] = bin2hex(random_bytes(32));

if (!isset($_SESSION['level']))
	$_SESSION['level']=0;

$answer = isset($_POST['answer'])? htmlspecialchars($_POST['answer']) : '';
if ($_SESSION['level'] != $problem_count &&
	$answer == $correct_answers[$_SESSION['level']] &&
	hash_equals($_POST['token_auth'],$_SESSION['token_auth']))
	$_SESSION['level']++;

$i = $_SESSION['level'];
if ($i < $problem_count)
	include "auth.php";
else
	include "calc.php";
?>
</html>