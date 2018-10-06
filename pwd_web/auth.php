<script type="text/javascript">
	$(document).ready(setTimeout(function(){
		$("#answer").focus();
	},1000));
</script>
<body data-n-head="">
	<div data-server-rendered="true" id="__nuxt">
		<div class="progress" style="width:0%;height:2px;background-color:#3B8070;opacity:0;"></div>
		<div>
			<section class="container" id="mine_container">
				<div class="card-wrap">
					<div class="card cardIn">
						<div class="title">
							<div>Auth <?php echo $i+1; ?></div>
						</div>
						<div class="question-content">
							<div class="question-text">
								<?php echo $problem[$i]; ?>
							</div>
							<form method="post" action="">
								<div class="question-input">
									<input id="answer" name="answer" value="" class="input">
								</div>
								<br/>
								<input type='hidden' name='token_auth' value="<?php echo $_SESSION['token_auth'];?>">
								<div>
									<input type="submit" value="Submit" class="btn-mine btn-secondary button-mine">
								</div>
							</form>
						</div>
					</div>
				</div>
			</section>
		</div>
	</div>
</body>