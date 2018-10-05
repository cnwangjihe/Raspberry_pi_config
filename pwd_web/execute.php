<?php
	session_start();
	include "settings.php";
	if ($_SESSION["level"] != $problem_count)
		die("You have not finish the problem yet");

	if ($_POST["CSRF"]!=$_SESSION["csrf_token_name"])
		die("Cross-site Request Forgery Detected");

	$arg[0]=$_POST["Text"];
	$arg[1]=$_POST["Passwd"];
	$arg[2]=$_POST["Security"];
	$arg[3]=$_POST["Length"];
	$arg[4]=$_POST["Type"];
	$cmd="/usr/bin/passwdg ";
	for ($i = 0; $i < 5; $i ++)
	{
		if (strpos($arg[$i], "'") !== false)
			die("Texts {$i} include ', but it is not allowed");
		$arg[$i]="'".$arg[$i]."'";
		$cmd=$cmd." ".$arg[$i];
	}
	echo shell_exec($cmd);
?>