<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="description" content="On-Line вычислитель и интегратор" />
    <meta name="keywords" content="Вычисление, математика, интеграл, on-line, equation, integrator" />
    <title>On-Line вычислитель</title>
    <link href="style.css" rel="stylesheet" type="text/css" />
    
    <script language="JavaScript">
      function setDefaultStyle()
      {
        var txtEquation = document.getElementById("txtEquation");
        var txtLower = document.getElementById("txtLower");
        var txtUpper = document.getElementById("txtUpper");
        var txtPrecision = document.getElementById("txtPrecision");
        
        txtEquation.style.border  = "1px solid #000000";
        txtPrecision.style.border = "1px solid #000000";
        txtLower.style.border     = "1px solid #000000";
        txtUpper.style.border     = "1px solid #000000";
      } /* End of 'setDefaultStyle' function */
      
      function validateForm(frm)
      {
        setDefaultStyle();
        var txtEquation = document.getElementById("txtEquation");
        var txtLower = document.getElementById("txtLower");
        var txtUpper = document.getElementById("txtUpper");
        var txtPrecision = document.getElementById("txtPrecision");
        
        var isValid = true;
        
        if (txtPrecision.value.length == 0)
        {          
          txtPrecision.style.border = "1px solid #ff0000";
          isValid = false;
          txtPrecision.focus();
        }
        
        if (txtUpper.value.length == 0)
        {          
          txtUpper.style.border = "1px solid #ff0000";
          isValid = false;
          txtUpper.focus();
        }
        
        if (txtLower.value.length == 0)
        {          
          txtLower.style.border = "1px solid #ff0000";
          isValid = false;
          txtLower.focus();
        }
        
        if (txtEquation.value.length == 0)
        {          
          txtEquation.style.border = "1px solid #ff0000";
          isValid = false;
          txtEquation.focus();
        }    

        return isValid;
      } /* End of 'validateForm' function */
      
      function resetForm()
      {
        setDefaultStyle();
        var txtEquation = document.getElementById("txtEquation");
        var txtLower = document.getElementById("txtLower");
        var txtUpper = document.getElementById("txtUpper");
        var txtPrecision = document.getElementById("txtPrecision");

        txtEquation.value = "";
        txtPrecision.value = "0.00001";
        txtLower.value = "";
        txtUpper.value = "";
        
        txtEquation.focus();
      } /* End of 'resetForm' function */
      
      function submitForm(frm)
      {
        if (validateForm(frm))
          return frm.submit();
        return false;
      } /* End of 'submitForm' function */
      
      function setHintPosition()
      {
        var div=document.getElementById("divHint");
        div.style.left = (parseInt(document.body.clientWidth)  - parseInt(div.clientWidth))  / 2 + "px";
        div.style.top  = (parseInt(document.body.clientHeight) - parseInt(div.clientHeight)) / 2 + "px";
      } /* End of 'setHintPosition' function */
      
      function showHint()
      {
        var divHint = document.getElementById("divHint");
        divHint.style.display = 'block';
        setHintPosition();
        return true;
      } /* End of 'showHint' function */
      
      function hideHint()
      {
        var divHint = document.getElementById("divHint");
        divHint.style.display = 'none';
      } /* End of 'hideHint' function */
    </script>
  </head>
  <body>
    <?php
      error_reporting(~E_ALL); 
      
      $equation = "";
      $lower = "";
      $upper = "";
      $result = "";
      $directory  = "c:\\webservers\\bin\\calculator\\";
      $calculator = $directory."integrator_rel.exe";
      $precision = "0.00001";
      
      $checkedRect = "checked";
      $checkedSimp = "";
      
      function IsPostBack()
      {
        return ($_SERVER['REQUEST_METHOD'] == 'POST');
      } /* End of 'IsPostBack ' function */
    
      function ParseOutput($output, $x)
      {
        list($messageType, $result) = split('=', $output);
        if ($messageType == "error")
          return $result;
        
        list($value, $iterations) = split(';', $result);
        return "&int;f(x)dx = $value; Number of iterations = $iterations";
      } /* End of 'ParseOutput' function */
      
      /* Process equation */
      if (IsPostBack())
      {        
        $equation  = preg_replace("([^a-zA-Z0-9\-\+\*\/\^\.\s\(\)])", "", $_POST['txtEquation']);
        $lower     = preg_replace("([^0-9\.\-])", "", $_POST['txtLower']);
        $upper     = preg_replace("([^0-9\.\-])", "", $_POST['txtUpper']);
        $precision = preg_replace("([^0-9\.\-])", "", $_POST['txtPrecision']);
        $method    = preg_replace("([^a-zA-Z])", "",  $_POST['rbMethod']);
        
        if ($method == "simp")
        {
          $checkedSimp = "checked";
          $checkedRect = "";
        }
        
        /* Storing equation to file */
        $fname = $directory.md5($equation.time()).".eq";
        $file = fopen($fname, "wt");
        fputs($file, $equation);
        fclose($file); 
         
        /* Equate */         
        $output = shell_exec("\"$calculator $fname $method $lower $upper $precision\"");
        $result = ParseOutput($output);  
        unlink($fname);
      }    
    ?>
    <table class="content" cellspacing="0" cellpadding="0" border="0">
      <tr height="60 px">
        <td><h1 class="title">On-Line integrator</h1>
        </td>
      </tr>
      <tr height="30 px">
        <td>&nbsp;</td>
      </tr>
      <form action="integrate.php" method="post" id="frmEquation" onSubmit="return submitForm(this);">
      <tr height="50 px">
        <td valign="top" align="center">Input integrand<br/>          
            &int; <input type="text" maxlength="512" style="width: 600px" name="txtEquation" id="txtEquation" tabindex="1" value="<?php echo $equation; ?>" /> dx   
        </td>
      </tr>
      <tr height="120 px">
        <td align="center">
          <table border="0" cellspacing="0" cellpadding="0">
            <tr height="40 px">
              <td>
                Lower limit = <input type="text" maxlength="8" style="width: 85px" name="txtLower" id="txtLower" tabindex="2" value="<?php echo $lower; ?>" /><br/>        
              </td>
              <td style="width: 20px">&nbsp;</td>
              <td>
                <input type="radio" name="rbMethod" value="rect" <?php echo $checkedRect; ?> /> Left Rectangles method
              <td>
            </tr>
            <tr height="40 px">
              <td>   
                Upper limit = <input type="text" maxlength="8" style="width: 85px" name="txtUpper" id="txtUpper" tabindex="3" value="<?php echo $upper; ?>" /><br/>
              </td>
              <td style="width: 20px">&nbsp;</td>
              <td>
                <input type="radio" name="rbMethod" value="simp" <?php echo $checkedSimp; ?> /> Simpson's method
              </td>             
            </tr>
            <tr height="40 px">
              <td>   
                &nbsp;&nbsp;Precision = <input type="text" maxlength="8" style="width: 85px" name="txtPrecision" id="txtPrecision" tabindex="4" value="<?php echo $precision; ?>" /><br/>
              </td>
              <td style="width: 20px">&nbsp;</td>
              <td>&nbsp;</td>
            </tr>
          </table>
        </td>
      </tr>
      <tr height="40 px">
        <td>
          <input type="submit" value="Integrate" tabindex="5" style="width: 150px" /> 
          <input type="button" value="Reset" tabindex="6" style="width: 150px" onclick="return resetForm();" />
        </td>
      </tr>
      </form>  
      <tr height="40 px">
        <td>&nbsp;<?php echo $result; ?>&nbsp;</td>
      </tr>
      </tr>
      <tr>
        <td valign="top">
          <a href="#" onclick="return showHint();">Grammar</a> | <a href="index.php">Calculator</a>
        </td>
      </tr>
    </table>
    <div id="divHint" class="grammar">
      <table border="0" cellspacing="4" cellpadding="0" width="100%">
        <tr height="20px">
          <td colspan="2"><b>Terminals sets</b></td>
        </tr>
        <tr>
          <td valign="top" colspan="2">
            Consts = {E, PI}<br/>
            Variables = {x}<br/>
            Operators = {+, -, *, /, ^}<br/>
            Functions = {Exp, Log, Sin, Cos, Tg, Ctg, Sh, Ch}<br/>
            Symbols = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}<br/>
            Digits = {0,1,2,3,4,5,6,7,8,9}<br/>
          </td>
        </tr>
        <tr>
          <td colspan="2"><br/><b>Terminals</b></td>    
        </tr>
        <tr>
          <td valign="top">
            Const &isin; Consts (C = Const)<br/>
            Variable &isin; Variables (V = Variable)<br/>
            Operator &isin; Operators (O = Operator)<br/>
          </td>                
          <td valign="top">
            Function &isin; Functions (F = Function)<br/>
            Symbol &isin; Symbols (S = Symbol)<br/>
            Digit &isin; Digits (D = Digit)</br>          
          </td>
        </tr>
        <tr>
          <td colspan="2"><br/><b>Non-terminals</b></td>
        </tr>   
        <tr>
          <td valign="top" colspan="2">
            Token = Symbol<sup>+</sup> (T = Token)<br/>
            Number = Digit<sup>+</sup> (N = Number)<br/>
            Parameter = Token &notin; (Consts &cup; Variables &cup; Functions)<sup> </sup> (P = Parameter)<br/>    
          </td>
        </tr>     
        <tr>
          <td colspan="2"><br/><b>Equation</b></td>
        </tr>  
        <tr>
          <td colspan="2">
            Equation = C | V | F(Equation) | (Equation O Equation) | P
          </td>
        </tr>        
        <tr>
          <td colspan="2" align="center">
            <br/>
            <a href='#' onclick="return hideHint();">Close</a>
          </td>
        </tr>
      </table>
    </div>
  </body>
  <script language="JavaScript">
    var txtEquation = document.getElementById("txtEquation");
    txtEquation.focus();
  </script>
</html>