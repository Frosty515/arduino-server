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