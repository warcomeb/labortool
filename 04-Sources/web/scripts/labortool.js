/*
 * LabOrTool 
 * Copyright (C) 2018-2019 Marco Giammarini <http://www.warcomeb.it>
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
 */

$(document).ready(function() 
{
    $('#labortool-logout').on("click",userLogout);

    // Data table setup
    if ($('#user-list-table').length)
    {
        $('#user-list-table').DataTable();
    }

    // Datetime picker enable
    moment.locale('it');
    $('#datetimepicker1').datetimepicker({
    	    format: 'DD/MM/YYYY',
    });

    if ($('#add-user').length)
    {
        console.log("INFO: #add-user exist!");

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
    }

    if ($('#add-customer').length)
    {
        console.log("INFO: #add-customer exist!");

        $('#add-customer').parsley().on('form:success', function() 
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
                'address'           : $('#inputAddress').val(),
                'city'              : $('#inputCity').val(),
                'district'          : $('#inputDistrict').val(),
                'zip'               : $('#inputZip').val(),
                'country'           : $('#inputCountry').val(),
                'website'           : $('#inputWebsite').val(),
                'email'             : $('#inputEmail').val(),
                'phone'             : $('#inputPhone').val(),
                'fax'               : $('#inputFax').val(),
                'vat'               : $('#inputVAT').val(),
                'nin'               : $('#inputNIN').val(),
                'iban'              : $('#inputIBAN').val(),
                'note'              : $('#inputNote').val(),
                'customer'          : $("#inputCustomerCheck").is(":checked") ? 1 : 0,
                'supplier'          : $("#inputSupplierCheck").is(":checked") ? 1 : 0,
                'private'           : $("#inputPrivateCheck").is(":checked") ? 1 : 0,
            };
           
           
            // Don't submit form
            return false;
        });
    }

    /*
     * User logout function
     */
    function userLogout ()
    {
        console.log("INFO: LogOut request...");

        $.ajax({
            type        : 'POST',
            url         : '/prjform/logoutuser.form.php',
            data        : null, 
            dataType    : 'json',
            encode      : true
        })
        .done(function(data)
        {
            console.log("INFO: LogOut done!");

            // Redirect to login page...
            $(location).attr('href', '/home/home');
        });
    }
});