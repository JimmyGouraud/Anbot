<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Anbot - pâtisserie</title>
    <meta name="description" content="Web Crawler by Jimmy">
    <meta name="keywords" content="Browse the various job websites and collect the data.">

    <link rel="stylesheet" type="text/css" href="https://fonts.googleapis.com/css?family=Open+Sans|Candal|Alegreya+Sans">
    <link rel="stylesheet" type="text/css" href="css/font-awesome.min.css">
    <link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="css/imagehover.min.css">
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <link rel="stylesheet" type="text/css" href="css/my_css.css">

    <link rel="icon" type="image/png" href="img/logo-pineapple.png" />
  
  </head>
  <body>
    <!--Banner-->
    <div class="banner">
      <div class="bg-color">
        <div class="container">
          <div class="row">
            <div class="banner-text text-center">
              <div class="text-border">
                <h2 class="text-dec">Anbot - pâtisserie</h2>
              </div>
              <div class="intro-para text-center quote">
                <p class="big-text">
                  Browse the various job websites and collect the data.
                </p>
                <p class="small-text">
                  Web crawler by Jimmy
                </p>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <!--/ Banner-->

    <!-- Panel -->
    <section class="section-padding even">
      <div class="container">
	<div class="row">
          <form id="employmentType">
	    <div class="row">
	      <div class="col-md-6">
		<div class="row">
		  <div class="text-center col-md-12 col-sm-12">
		    <input type="checkbox" name="employmentType" value="all" onclick="check_all()"> tout<br>
		  </div>
		  <div class="col-md-6 col-sm-6">
		    <input type="checkbox" name="employmentType" value="permanent" onclick="update_display()"> CDI<br>
		    <input type="checkbox" name="employmentType" value="contract" onclick="update_display()"> CDD<br>
		    <input type="checkbox" name="employmentType" value="fulltime" onclick="update_display()"> Temps plein<br>
		    <input type="checkbox" name="employmentType" value="parttime" onclick="update_display()"> Temps partiel<br>
		  </div>
		  <div class="col-md-6 col-sm-6">
		    <input type="checkbox" name="employmentType" value="temporary" onclick="update_display()"> Intérim<br>
		    <input type="checkbox" name="employmentType" value="subcontract" onclick="update_display()"> Freelance / Indépendant<br>
		    <input type="checkbox" name="employmentType" value="apprenticeship" onclick="update_display()"> Apprentissage / Alternance<br>
		    <input type="checkbox" name="employmentType" value="internship" onclick="update_display()"> Stage<br>
		  </div>
		</div>
	      </div>
	    </div>
	  </form> 
	</div>
      </div>
    </section>
    <!--/ Panel -->

    <!-- Offers-->
    <?php include("../server/offers.php"); ?>
    <!--/ Offers-->

    <!--Footer-->
    <footer id="footer" class="footer">
      <div class="container text-center">
        ©2016 Mentor Theme. All rights reserved
        <div class="credits">
            <!--
                All the links in the footer should remain intact.
                You can delete the links only if you purchased the pro version.
                Licensing information: https://bootstrapmade.com/license/
                Purchase the pro version with working PHP/AJAX contact form: https://bootstrapmade.com/buy/?theme=Mentor
            -->
            Designed by <a href="https://bootstrapmade.com/">Free Bootstrap Themes</a>
        </div>
      </div>
    </footer>
    <!--/ Footer-->


    
    <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.4.4/jquery.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
    
    <script src="js/sortOffers.js"></script>
    <script src="js/test.js"></script>
  </body>
</html>
