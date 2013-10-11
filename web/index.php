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
        var txtVariable = document.getElementById("txtVariable");
        
        txtEquation.style.border = "1px solid #000000";
        txtVariable.style.border = "1px solid #000000";
      } /* End of 'setDefaultStyle' function */
      
      function validateForm(frm)
      {
        setDefaultStyle();
        var txtEquation = document.getElementById("txtEquation");
        var txtVariable = document.getElementById("txtVariable");
        
        var isValid = true;
        
        if (txtVariable.value.length == 0)
        {          
          txtVariable.style.border = "1px solid #ff0000";
          isValid = false;
          txtVariable.focus();
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
        var txtVariable = document.getElementById("txtVariable");
        txtEquation.value = "";
        txtVariable.value = "";
        
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
      $result = "";
      $directory  = "c:\\webservers\\bin\\calculator\\";
      $calculator = $directory."calculator_rel.exe";
      
      function IsPostBack()
      {
        return ($_SERVER['REQUEST_METHOD'] == 'POST');
      } /* End of 'IsPostBack ' function */
    
      function ParseOutput($output, $x)
      {
        list($messageType, $result) = split('=', $output);
        if ($messageType == "error")
          return $result;
        return "f($x) = $result";
      } /* End of 'ParseOutput' function */
      
      /* Process equation */
      if (IsPostBack())
      {        
        $equation = preg_replace("([^a-zA-Z0-9\-\+\*\/\^\.\s\(\)])", "", $_POST['txtEquation']);
        $variable = preg_replace("([^0-9\.\-])", "", $_POST['txtVariable']);
        
        /* Storing equation to file */
        $fname = $directory.md5($equation.time()).".eq";
        $file = fopen($fname, "wt");
        fputs($file, $equation);
        fclose($file); 
         
        /* Equate */         
        $output = shell_exec("\"$calculator $fname $variable\"");
        $result = ParseOutput($output, $variable);  
        unlink($fname);
      }    
    ?>
    <table class="content" cellspacing="0" cellpadding="0" border="0">
      <tr height="60 px">
        <td><h1 class="title">On-Line calculator</h1>
        </td>
      </tr>
      <tr height="30 px">
        <td>&nbsp;</td>
      </tr>
      <form action="index.php" method="post" id="frmEquation" onSubmit="return submitForm(this);">
      <tr height="50 px">
        <td valign="top" align="center">Input equation<br/>          
            f(x) = <input type="text" maxlength="512" style="width: 600px" name="txtEquation" id="txtEquation" tabindex="1" value="<?php echo $equation; ?>" />                
        </td>
      </tr>
      <tr height="40 px">
        <td>
          x = <input type="text" maxlength="8" style="width: 85px" name="txtVariable" id="txtVariable" tabindex="2" />
        </td>
      </tr>
      <tr height="40 px">
        <td>
          <input type="submit" value="Calculate" tabindex="3" style="width: 150px" /> 
          <input type="button" value="Reset" tabindex="4" style="width: 150px" onclick="return resetForm();" /></td>
      </tr>
      </form>  
      <tr height="40 px">
        <td>&nbsp;<?php echo $result;?>&nbsp;</td>
      </tr>
      <tr height="80 px">
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td valign="top">
          <a href="#" onclick="return showHint();">Grammar</a> | <a href="integrate.php">Integrator</a>
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
    var txtVariable = document.getElementById("txtVariable");
    <?php 
      if (IsPostBack())
        echo "txtVariable";
      else 
        echo "txtEquation";
    ?>.focus();
  </script>
</html>
