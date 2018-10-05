<?php
	session_start();
	include "settings.php";
	if ($_SESSION["level"] != $problem_count)
	{
		echo "You have not finish the problem yet!";
		return "f**k";
	}
	if ($_POST["CSRF"]!=$_SESSION["csrf_token_name"])
	{
		echo "Cross-site Request Forgery Detected!";
		return "f**k";
	}
	echo shell_exec("../cryptopp/main {$_POST["Text"]} {$_POST["Passwd"]} {$_POST["Security"]} {$_POST["Length"]} {$_POST["Type"]}");
?>