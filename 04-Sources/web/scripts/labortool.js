/******************************************************************************
 * LabOrTool 
 * Copyright (C) 2018 Marco Giammarini <http://www.warcomeb.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Author:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 ******************************************************************************/

$(document).ready(function() 
{
	// Data table setup
    $('#user-list-table').DataTable();
    
    // Datetime picker enable
    moment.locale('it');
    $('#datetimepicker1').datetimepicker({
    	    format: 'DD/MM/YYYY',
    });
	
	// New rule validator
	window.Parsley
	  .addValidator('provincia', {
	      requirementType: 'string',
	      validateString: function(value, requirement) 
	      {
	    	      reg = /^[a-zA-Z]{2}$/;
	          return reg.test(value);
	      },
	      messages: {
	          en: 'This string should be only two char',
	          it: 'La sigla della Provincia deve essere di sole due lettere'
	      }
	  })
	  .addValidator('zipCode', {
	      requirementType: 'string',
	      validateString: function(value, requirement) 
	      {
	    	      reg = /^[0-9]{5}$/;
	          return reg.test(value);
	      },
	      messages: {
	          en: 'The ZIP code should be five number',
	          it: 'Il CAP deve essere costituito da 5 numeri'
	      }
	  })
	  .addValidator('nin', {
	      requirementType: 'string',
	      validateString: function(value, requirement) 
	      {
	    	      reg = /^[a-zA-Z]{6}[0-9]{2}[a-zA-Z][0-9]{2}[a-zA-Z][0-9]{3}[a-zA-Z]$/;
	          return reg.test(value);
	      },
	      messages: {
	          en: 'The NIN code should be in Italian format',
	          it: 'Il formato del codice fiscale è sbagliato'
	      }
	  })
	  .addValidator('phone', {
	      requirementType: 'string',
	      validateString: function(value, requirement) 
	      {
	    	      reg = /^(\+[0-9]{1,3})?( |\-)?[0-9]{1,3}( |\-)?[0-9]{3,5}( |\-)?[0-9]{3,4}(( |\-)?[0-9]{3})?$/;
	          return reg.test(value);
	      },
	      messages: {
	          en: 'The phone number was in the wrong format',
	          it: 'Il numero di telefono non è valido'
	      }
	  })
	  .addValidator('password', {
	      requirementType: 'string',
	      validateString: function(value, requirement) 
	      {
	    	      reg = /^[0-9a-zA-Z]{8,}$/;
	          return reg.test(value);
	      },
	      messages: {
	          en: 'The password must containat least 8 alphanumeric characters',
	          it: 'La password deve contenere almeno 8 caratteri alfanumerici'
	      }
	  })
	  .addValidator('birthday', {
          validateString: function(value, minAge) 
          {
              var birthday = moment(value, "DD/MM/YYYY");
              var today = moment(new Date());

              // Check only if the birthday date is greater then today
              var test = today.diff(birthday);
              if (test > 0) return true;
              else return false;
	      },
	      messages: {
	          en: 'Birthday must not be greater than today',
	          it: 'La data di nascita deve essere antecedente ad oggi'
	      }
	  });
	  	  
	

    $('#add-user').parsley().on('form:success', function() 
    	{
    	    // TODO: do somethings?
    })
    .on('form:error', function() 
    	{
	    // TODO: do somethings?
    })
    .on('form:submit', function() 
    {
	    var formData = {
	        'name'              : $('#inputName').val(),
	        'surname'           : $('#inputSurname').val(),
	        'password'          : CryptoJS.SHA256($('#inputPassword').val()).toString(CryptoJS.enc.Hex),
	        'email'             : $('#inputEmail').val(),
	        'phone'             : $('#inputPhone').val(),
	        'address'           : $('#inputAddress').val(),
	        'city'              : $('#inputCity').val(),
	        'district'          : $('#inputDistrict').val(),
	        'zip'               : $('#inputZip').val(),
	        'country'           : $('#inputCountry').val(),
	        'nin'               : $('#inputNIN').val(),
	        'birthday'          : $('#inputBirthday').val(),
	        'note'              : $('#inputNote').val(),
	    };
    
	    // Disable buttons
        $('#add-user-save').attr("disabled","disabled");
        $('#add-user-reset').attr("disabled","disabled");
        // Show loading gift
	    $('#add-user-loading').removeClass('d-none').delay(800);
	    
        $.ajax({
            type        : 'POST',
            url         : '/prjform/adduser.form.php',
            data        : formData, 
            dataType    : 'json',
            encode      : true
        })
        .done(function(data)
        {
            // Just for debug
            //console.log(data);

            // NO ERRORS
            if (0 === data['status'])
            {
        	        // Show success message
                $('#add-user-loading').addClass('d-none');
                $('#add-user-error').addClass('d-none');
                $('#add-user-success').removeClass('d-none').delay(2000);
                
                // Redirect to view page...
                $(location).attr('href', '/records/employee/view/' + data['id']);
            }
            else if (1 === data['status'])
            {
        	    	    // Write text into error div message
        	    	    $('#add-user-error').html('<i class="fas fa-times"></i>');
        	    	    $('#add-user-error').append(' ' + data['status']);

        	        // Show error message
                $('#add-user-loading').addClass('d-none');
                $('#add-user-success').addClass('d-none');
                $('#add-user-error').removeClass('d-none').delay(2000);
                
        	        // Enable buttons
                $('#add-user-save').removeAttr("disabled");
                $('#add-user-reset').removeAttr("disabled");
            }
        })
        .fail(function(jqXHR, textStatus)
        	{
    	        // Write text into error div message
    	        $('#add-user-error').html('<i class="fas fa-times"></i>');
    	        $('#add-user-error').append(' ' + textStatus);

            // Show error message
            $('#add-user-loading').addClass('d-none');
            $('#add-user-success').addClass('d-none');
            $('#add-user-error').removeClass('d-none').delay(2000);
    
            // Enable buttons
            $('#add-user-save').removeAttr("disabled");
            $('#add-user-reset').removeAttr("disabled");
        	});

        // Don't submit form
        return false;
    });
});