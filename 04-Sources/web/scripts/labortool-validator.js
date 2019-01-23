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
    .addValidator('ninsupplier', {
        requirementType: 'string',
        validateString: function(value, requirement)
        {
            reg = /^(ATU[0-9]{8}|BE0[0-9]{9}|BG[0-9]{9,10}|CY[0-9]{8}L|CZ[0-9]{8,10}|DE[0-9]{9}|DK[0-9]{8}|EE[0-9]{9}|(EL|GR)[0-9]{9}|ES[0-9A-Z][0-9]{7}[0-9A-Z]|FI[0-9]{8}|FR[0-9A-Z]{2}[0-9]{9}|GB([0-9]{9}([0-9]{3})?|[A-Z]{2}[0-9]{3})|HU[0-9]{8}|IE[0-9]S[0-9]{5}L|IT[0-9]{11}|LT([0-9]{9}|[0-9]{12})|LU[0-9]{8}|LV[0-9]{11}|MT[0-9]{8}|NL[0-9]{9}B[0-9]{2}|PL[0-9]{10}|PT[0-9]{9}|RO[0-9]{2,10}|SE[0-9]{12}|SI[0-9]{8}|SK[0-9]{10})|([a-zA-Z]{6}[0-9]{2}[a-zA-Z][0-9]{2}[a-zA-Z][0-9]{3}[a-zA-Z])$/;
            return reg.test(value); 
        },
        messages: 
        {
            en: 'The NIN code shuld be a VATID or NIN in Italian format',
            it: 'Il formato del codice fiscale è sbagliato'
        }
    })
    .addValidator('vat', {
        requirementType: 'string',
        validateString: function(value, requirement)
        {
            reg = /^(ATU[0-9]{8}|BE0[0-9]{9}|BG[0-9]{9,10}|CY[0-9]{8}L|CZ[0-9]{8,10}|DE[0-9]{9}|DK[0-9]{8}|EE[0-9]{9}|(EL|GR)[0-9]{9}|ES[0-9A-Z][0-9]{7}[0-9A-Z]|FI[0-9]{8}|FR[0-9A-Z]{2}[0-9]{9}|GB([0-9]{9}([0-9]{3})?|[A-Z]{2}[0-9]{3})|HU[0-9]{8}|IE[0-9]S[0-9]{5}L|IT[0-9]{11}|LT([0-9]{9}|[0-9]{12})|LU[0-9]{8}|LV[0-9]{11}|MT[0-9]{8}|NL[0-9]{9}B[0-9]{2}|PL[0-9]{10}|PT[0-9]{9}|RO[0-9]{2,10}|SE[0-9]{12}|SI[0-9]{8}|SK[0-9]{10})$/;
            return reg.test(value); 
        },
        messages: 
        {
            en: 'The VATID code is not of a European Country',
            it: 'Il formato della P.IVA è sbagliato'
        }
    })
    .addValidator('iban', {
        requirementType: 'string',
        validateString: function(value, requirement)
        {
            reg = /^(?:(?:IT|SM)\d{2}[A-Z]\d{22}|CY\d{2}[A-Z]\d{23}|NL\d{2}[A-Z]{4}\d{10}|LV\d{2}[A-Z]{4}\d{13}|(?:BG|BH|GB|IE)\d{2}[A-Z]{4}\d{14}|GI\d{2}[A-Z]{4}\d{15}|RO\d{2}[A-Z]{4}\d{16}|KW\d{2}[A-Z]{4}\d{22}|MT\d{2}[A-Z]{4}\d{23}|NO\d{13}|(?:DK|FI|GL|FO)\d{16}|MK\d{17}|(?:AT|EE|KZ|LU|XK)\d{18}|(?:BA|HR|LI|CH|CR)\d{19}|(?:GE|DE|LT|ME|RS)\d{20}|IL\d{21}|(?:AD|CZ|ES|MD|SA)\d{22}|PT\d{23}|(?:BE|IS)\d{24}|(?:FR|MR|MC)\d{25}|(?:AL|DO|LB|PL)\d{26}|(?:AZ|HU)\d{27}|(?:GR|MU)\d{28})$/;
            return reg.test(value); 
        },
        messages: 
        {
            en: 'The IBAN code is not correct',
            it: 'Il formato dell\'IBAN è sbagliato'
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
//});