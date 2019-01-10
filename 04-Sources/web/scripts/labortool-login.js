/*
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
 */

$(document).ready(function() 
{
    // Login form
    $('#login-user').parsley().on('form:success', function() 
    {
    // TODO: do somethings?
    })
    .on('form:error', function() 
    {
    // TODO: do somethings?
    })
    .on('form:submit', function() 
    {
        var password = CryptoJS.SHA256($('#inputPassword').val()).toString(CryptoJS.enc.Hex);
        var mycrypto = password + $('#inputKey').val();
        var formData = 
        {
            'username' : $('#inputUsername').val(),
            'password' : CryptoJS.SHA256(mycrypto).toString(CryptoJS.enc.Hex),
		};
	    
        $.ajax({
            type        : 'POST',
            url         : '/prjform/loginuser.form.php',
            data        : formData, 
            dataType    : 'json',
            encode      : true
        })
        .done(function(data)
        {
            console.log("INFO: Ajax command success!");
            console.log("INFO: Status " + data[0]);

            if (_LOGIN__USER_LOGGED_IN === data[0])
            {
                // Write text into error div message
                $('#login-message').html('<i class="fas fa-check"></i>');
                $('#login-message').append(' LogIn completato!');

                $('#login-message').addClass('alert-success');
                $('#login-message').removeClass('alert-primary').delay(2000);

                // Redirect to view page...
                $(location).attr('href', '/home/home');
            }
            else
            {

            }
        })
        .fail(function(jqXHR, textStatus)
        {
            console.log("INFO: login fail!");
        });
	    
        // Don't submit form
        return false;
    });

});