$(document).ready(function(){
    var checkboxes = $("#employmentType [name=\"employmentType\"]");
    
    for (var i = 0; i < checkboxes.length; i++)
    {
	checkboxes[i].checked = true;
    }
});


function check_all()
{
    var checkbox_all = $("#employmentType [name=\"employmentType\"][value=\"all\"]");
    var checkboxes = $("#employmentType [name=\"employmentType\"]");
    
    for (var i = 1; i < checkboxes.length; i++)
    {
	checkboxes[i].checked = checkbox_all.attr("checked");
    }
    update_display();
}


function update_display()
{
    var all_check = true;
    
    var checkboxes = $("#employmentType [name=\"employmentType\"]");
    for (var i = 1; i < checkboxes.length; i++)
    {
	if (!checkboxes[i].checked)
	{
	    all_check=false;
	}
	
	var offers = $("." + checkboxes[i].value);
	for (var j = 0; j < offers.length; j++)
	{
	    if (checkboxes[i].checked)
	    {
		$(offers[j]).show();
	    }
	    else
	    {		
		var classes = offers[j].getAttribute("class").split(' ');
		$(offers[j]).hide();
		for (var k = 0; k < classes.length; k++)
		{
		    var checkbox = $("#employmentType [name=\"employmentType\"][value=\"" + classes[k] + "\"]");
		    
		    if (checkbox.attr("checked"))
		    {
			$(offers[j]).show();
			break;
		    }
		}
	    }
	}
    }
    
    checkboxes[0].checked = all_check;
}

