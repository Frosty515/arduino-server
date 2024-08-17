/*
Copyright (©) 2024  Frosty515

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

$.ajaxSetup({async:false});

/**
 * Returns the state of the pin
 * @param {Number} pin
 * @returns {Boolean}
 */
function getPinState(pin) {
    let returnValue;
    $.post("/api/get-pin-state", {pin: pin}, function(data) {
        returnValue = JSON.parse(data).value;
    });
    return returnValue;
}

/**
 * Sets the state of the pin
 * @param {Number} pin
 * @param {Boolean} value
 */
function setPinState(pin, value) {
    $.post("/api/set-pin-state", {pin: pin, value: value});
}

/**
 * Configures the mode of the pin
 * @param {Number} pin
 * @param {String} mode
 */
function configPinMode(pin, mode) {
    $.post("/api/config-pin-mode", {pin: pin, mode: mode});
}