<script type="text/javascript">
	$(document).ready(function(){
	  $("button#submit").click(function(){
	  	$.post("execute.php",
	  	{
	  	  Text:$("#Text").val(),
	  	  Passwd:$("#Passwd").val(),
	  	  Security:$("#Security").val(),
	  	  Length:$("#Length").val(),
	  	  Type:$("#Type").val(),
	  	},
	  	function(data,status){
	  		$("#Result").text(data);
	  		$('#Result_Modal').modal('show');
	  	});
	  });
	});
</script>
<body data-n-head="">
	<div data-server-rendered="true" id="__nuxt">
		<div class="progress" style="width:0%;height:2px;background-color:#3B8070;opacity:0;"></div>
		<div>
			<section class="container" id="mine_container">
				<div class="card-wrap">
					<div class="card cardIn">
						<div class="title">
							<div>Calc</div>
						</div>
						<div class="question-content">
							<!---->
							<div class="question-input">
								<input placeholder="Enter plain text..." value="" id="Text" class="input">
								<br/>
								<input placeholder="Enter password..." type="password" id="Passwd" value="" class="input">
							</div>
							<div>
								<label>Security</label>
								<select class="selectpicker" title="Security level..." id="Security" name="Security">
									<?php
									for ($x = 0; $x < 10; $x ++) {
										echo "<option value=\"$x\">$x</option>";
									}
									?>
								</select>
							</div>
							<div>
								<label>Length</label>
								<select class="selectpicker" title="Length..." id="Length" name="Length">
									<option value="0">8</option>
									<option value="1">16</option>
									<option value="2">32</option>
									<option value="3">40</option>
									<option value="4">48</option>
									<option value="5">56</option>
									<option value="6">64</option>
									<option value="7">80</option>
									<option value="8">96</option>
									<option value="9">128</option>
								</select>
							</div>
							<div>
								<label>Type</label>
								<select class="selectpicker" title="Type..." id="Type" name="Type">
									<option value="0">Hex</option>
									<option value="1">Base64</option>
								</select>
							</div>
							<br/>
							<div>
								<button id="submit" class="button-mine btn-mine btn-secondary">Calc</button>
							</div>
						</div>
					</div>
				</div>
			</section>
		</div>
	</div>
	<div class="modal fade" id="Result_Modal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLongTitle" aria-hidden="true">
	  <div class="modal-dialog" role="document">
	    <div class="modal-content">
	      <div class="modal-header">
	        <h5 class="modal-title" id="exampleModalLongTitle">Result</h5>
	        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
	          <span aria-hidden="true">&times;</span>
	        </button>
	      </div>
	      <div class="modal-body" id="Result">
	        .........................................................................................................................................................................................................................................................................................................
	      </div>
	      <div class="modal-footer">
	        <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
	      </div>
	    </div>
	  </div>
	</div>
	<style>
		label {
		    font-size: 2.5vh;
		    width: 80px;
		}
		.question-input + * {
			margin-top: 10px;
		}

		.container>.card-wrap {
			height: 80vh;
		}
		.container>.card-wrap .card .question-content {
			top : 50%;
		}
		.bootstrap-select:not([class*=col-]):not([class*=form-control]):not(.input-group-btn) {
			width: 18vh;
		}
		div.modal-body{
			word-break:break-all;
		}
		.bootstrap-select>.dropdown-toggle {
		    line-height: 90%;
		}
	</style>
</body>