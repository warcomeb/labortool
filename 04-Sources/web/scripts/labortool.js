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

    // List of data table setup
    if ($('#user-list-table').length)
    {
        $('#user-list-table').DataTable();
    }
    if ($('#customer-list-table').length)
    {
        $('#customer-list-table').DataTable();
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

    if ($('#customersupplier-form').length)
    {
        console.log("INFO: #customersupplier-form exist!");

        $('#customersupplier-form-customer').on("change",{type : "customer"},supplierTypeSelect);
        $('#customersupplier-form-supplier').on("change",{type : "supplier"},supplierTypeSelect);
        $('#customersupplier-form-private').on("change",{type : "private"},supplierTypeSelect);

        if ("view" !== $('#customersupplier-form-type').val())
        {
            $('#customersupplier-form').parsley().on('form:success', function() 
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
                    'name'              : $('#customersupplier-form-name').val(),
                    'address'           : $('#customersupplier-form-address').val(),
                    'city'              : $('#customersupplier-form-city').val(),
                    'district'          : $('#customersupplier-form-district').val(),
                    'zip'               : $('#customersupplier-form-zip').val(),
                    'country'           : $('#customersupplier-form-country').val(),
                    'website'           : $('#customersupplier-form-website').val(),
                    'email'             : $('#customersupplier-form-email').val(),
                    'phone'             : $('#customersupplier-form-phone').val(),
                    'fax'               : $('#customersupplier-form-fax').val(),
                    'vat'               : $('#customersupplier-form-vat').val(),
                    'nin'               : $('#customersupplier-form-nin').val(),
                    'iban'              : $('#customersupplier-form-iban').val(),
                    'note'              : $('#customersupplier-form-note').val(),
                    'customer'          : $("#customersupplier-form-customer").is(":checked") ? 1 : 0,
                    'supplier'          : $("#customersupplier-form-supplier").is(":checked") ? 1 : 0,
                    'private'           : $("#customersupplier-form-private").is(":checked") ? 1 : 0,
                    'active'            : $("#customersupplier-form-status").is(":checked") ? 1 : 0,
                };

                // Disable buttons
                $('#customersupplier-form-save').attr("disabled","disabled");
                $('#customersupplier-form-reset').attr("disabled","disabled");
                // Show loading gift
                $('#customersupplier-form-loading').removeClass('d-none').delay(800);

                $.ajax({
                    type        : 'POST',
                    url         : '/prjform/' + $('#customersupplier-form-type').val() + 'customer.form.php',
                    data        : formData, 
                    dataType    : 'json',
                    encode      : true
                })
                .done(function(data)
                {
                    console.log("INFO: #customersupplier-form ajax done!");

                    // NO ERRORS
                    if (0 === data['status'])
                    {
                        // Show success message
                        $('#customersupplier-form-loading').addClass('d-none');
                        $('#customersupplier-form-error').addClass('d-none');

                        // TODO: write success message
                        $('#customersupplier-form-success').html('<i class="fas fa-check"></i>');
                        if ("edit" === $('#customersupplier-form-type').val())
                        {
                            $('#customersupplier-form-success').append(' Modifica effettuata con successo!');
                        }
                        else if ("add" === $('#customersupplier-form-type').val())
                        {
                            $('#customersupplier-form-success').append(' Salvataggio effettuato con successo!');
                        }
                        $('#customersupplier-form-success').removeClass('d-none').delay(1000);

                        // Redirect to view page...
                        $(location).attr('href', '/records/customersupplier/view/' + data['id']);
                    }
                    else if (1 === data['status'])
                    {
                        // Write text into error div message
                        $('#customersupplier-form-error').html('<i class="fas fa-times"></i>');
                        $('#customersupplier-form-error').append(' ' + data['status']);

                        // Show error message
                        $('#customersupplier-form-loading').addClass('d-none');
                        $('#customersupplier-form-success').addClass('d-none');
                        $('#customersupplier-form-error').removeClass('d-none').delay(1000);

                        // Enable buttons
                        $('#customersupplier-form-save').removeAttr("disabled");
                        $('#customersupplier-form-reset').removeAttr("disabled");
                    }
                })
                .fail(function(jqXHR, textStatus)
                {
                    console.log("INFO: #customersupplier-form ajax fail!");

                    // Write text into error div message
                    $('#customersupplier-form-error').html('<i class="fas fa-times"></i>');
                    $('#customersupplier-form-error').append(' ERR[001] Ajax request fail!');

                    // Show error message
                    $('#customersupplier-form-loading').addClass('d-none');
                    $('#customersupplier-form-success').addClass('d-none');
                    $('#customersupplier-form-error').removeClass('d-none').delay(1000);

                    // Enable buttons
                    $('#customersupplier-form-save').removeAttr("disabled");
                    $('#customersupplier-form-reset').removeAttr("disabled");
                });

                // Don't submit form
                return false;
            });
        }
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

    /**
     * Check and manage customer value based on customer type.
     */
    function supplierTypeSelect (event)
    {
        console.log("INFO: Supplier/Customer choice -> " + event.data.type);

        if ((event.data.type === "customer") || (event.data.type === "supplier"))
        {
            $('#customersupplier-form-private').prop('checked', false);
            $('#customersupplier-form-private').parent().removeClass("active");
            // Enable VATID
            $('#customersupplier-form-vat').removeAttr("disabled");
            $('#customersupplier-form-vat').attr("required","required");
        }
        else
        {
            $('#customersupplier-form-customer').prop('checked', false);
            $('#customersupplier-form-supplier').prop('checked', false);
            $('#customersupplier-form-customer').parent().removeClass("active");
            $('#customersupplier-form-supplier').parent().removeClass("active");
            // Disable VATID input field
            $('#customersupplier-form-vat').removeAttr("required");
            $('#customersupplier-form-vat').attr("disabled","disabled");
            $('#customersupplier-form-vat').val("");
        }
    }
});