<body data-n-head="">
	<div data-server-rendered="true" id="__nuxt">
		<div class="progress" style="width:0%;height:2px;background-color:#3B8070;opacity:0;"></div>
		<div>
			<section class="container">
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
									<input name="answer" value="" class="input">
								</div>
								<br/>
								<div>
									<input type="submit" value="Go" class="btn-mine btn-secondary button-mine">
								</div>
							</form>
						</div>
					</div>
				</div>
			</section>
		</div>
	</div>
</body>