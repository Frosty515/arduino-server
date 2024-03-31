configPinMode(1, "OUTPUT");
setPinState(1, true);
configPinMode(1, "INPUT");
console.log("Pin 1 has the state " + getPinState(1));

async function updatePinStates() {
    for (let i = 0; i < 14; i++) {
        if (document.getElementById('pin' + i + 'mode').textContent == 'OUTPUT') {
            document.getElementById('pin' + i).textContent = getPinState(i) ? 'HIGH' : 'LOW';
        }
        else {
            document.getElementById('pin' + i + 'state').textContent = getPinState(i) ? 'HIGH' : 'LOW';
        }
    }
}


window.onload = function() {
    updatePinStates();
    window.setInterval(updatePinStates, 1000);
    
    document.getElementById('pin0').addEventListener('click', function() {
        if (document.getElementById('pin0mode').textContent == 'OUTPUT') {
            setPinState(0, !getPinState(0));
            console.log('Pin 0 has the state ' + getPinState(0));
            document.getElementById('pin0').textContent = getPinState(0) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin1').addEventListener('click', function() {
        if (document.getElementById('pin1mode').textContent == 'OUTPUT') {
            setPinState(1, !getPinState(1));
            console.log('Pin 1 has the state ' + getPinState(1));
            document.getElementById('pin1').textContent = getPinState(1) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin2').addEventListener('click', function() {
        if (document.getElementById('pin2mode').textContent == 'OUTPUT') {
            setPinState(2, !getPinState(2));
            console.log('Pin 2 has the state ' + getPinState(2));
            document.getElementById('pin2').textContent = getPinState(2) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin3').addEventListener('click', function() {
        if (document.getElementById('pin3mode').textContent == 'OUTPUT') {
            setPinState(3, !getPinState(3));
            console.log('Pin 3 has the state ' + getPinState(3));
            document.getElementById('pin3').textContent = getPinState(3) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin4').addEventListener('click', function() {
        if (document.getElementById('pin4mode').textContent == 'OUTPUT') {
            setPinState(4, !getPinState(4));
            console.log('Pin 4 has the state ' + getPinState(4));
            document.getElementById('pin4').textContent = getPinState(4) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin5').addEventListener('click', function() {
        if (document.getElementById('pin5mode').textContent == 'OUTPUT') {
            setPinState(5, !getPinState(5));
            console.log('Pin 5 has the state ' + getPinState(5));
            document.getElementById('pin5').textContent = getPinState(5) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin6').addEventListener('click', function() {
        if (document.getElementById('pin6mode').textContent == 'OUTPUT') {
            setPinState(6, !getPinState(6));
            console.log('Pin 6 has the state ' + getPinState(6));
            document.getElementById('pin6').textContent = getPinState(6) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin7').addEventListener('click', function() {
        if (document.getElementById('pin7mode').textContent == 'OUTPUT') {
            setPinState(7, !getPinState(7));
            console.log('Pin 7 has the state ' + getPinState(7));
            document.getElementById('pin7').textContent = getPinState(7) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin8').addEventListener('click', function() {
        if (document.getElementById('pin8mode').textContent == 'OUTPUT') {
            setPinState(8, !getPinState(8));
            console.log('Pin 8 has the state ' + getPinState(8));
            document.getElementById('pin8').textContent = getPinState(8) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin9').addEventListener('click', function() {
        if (document.getElementById('pin9mode').textContent == 'OUTPUT') {
            setPinState(9, !getPinState(9));
            console.log('Pin 9 has the state ' + getPinState(9));
            document.getElementById('pin9').textContent = getPinState(9) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin10').addEventListener('click', function() {
        if (document.getElementById('pin10mode').textContent == 'OUTPUT') {
            setPinState(10, !getPinState(10));
            console.log('Pin 10 has the state ' + getPinState(10));
            document.getElementById('pin10').textContent = getPinState(10) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin11').addEventListener('click', function() {
        if (document.getElementById('pin11mode').textContent == 'OUTPUT') {
            setPinState(11, !getPinState(11));
            console.log('Pin 11 has the state ' + getPinState(11));
            document.getElementById('pin11').textContent = getPinState(11) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin12').addEventListener('click', function() {
        if (document.getElementById('pin12mode').textContent == 'OUTPUT') {
            setPinState(12, !getPinState(12));
            console.log('Pin 12 has the state ' + getPinState(12));
            document.getElementById('pin12').textContent = getPinState(12) ? 'HIGH' : 'LOW';
        }
    });
    document.getElementById('pin13').addEventListener('click', function() {
        if (document.getElementById('pin13mode').textContent == 'OUTPUT') {
            setPinState(13, !getPinState(13));
            console.log('Pin 13 has the state ' + getPinState(13));
            document.getElementById('pin13').textContent = getPinState(13) ? 'HIGH' : 'LOW';
        }
    });

    document.getElementById('pin0mode').addEventListener('click', function() {
        if (document.getElementById('pin0mode').textContent == 'OUTPUT') {
            document.getElementById('pin0').style.display = 'none';
            document.getElementById('pin0state').textContent = getPinState(0) ? 'HIGH' : 'LOW';
            document.getElementById('pin0state').style.display = 'block';
            document.getElementById('pin0mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin0').textContent = getPinState(0) ? 'HIGH' : 'LOW';
            document.getElementById('pin0').style.display = 'block';
            document.getElementById('pin0state').style.display = 'none';
            document.getElementById('pin0mode').textContent = 'OUTPUT';
        }
        configPinMode(0, document.getElementById('pin0mode').textContent);
    });
    document.getElementById('pin1mode').addEventListener('click', function() {
        if (document.getElementById('pin1mode').textContent == 'OUTPUT') {
            document.getElementById('pin1').style.display = 'none';
            document.getElementById('pin1state').textContent = getPinState(1) ? 'HIGH' : 'LOW';
            document.getElementById('pin1state').style.display = 'block';
            document.getElementById('pin1mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin1').textContent = getPinState(1) ? 'HIGH' : 'LOW';
            document.getElementById('pin1').style.display = 'block';
            document.getElementById('pin1state').style.display = 'none';
            document.getElementById('pin1mode').textContent = 'OUTPUT';
        }
        configPinMode(1, document.getElementById('pin1mode').textContent);
    });
    document.getElementById('pin2mode').addEventListener('click', function() {
        if (document.getElementById('pin2mode').textContent == 'OUTPUT') {
            document.getElementById('pin2').style.display = 'none';
            document.getElementById('pin2state').textContent = getPinState(2) ? 'HIGH' : 'LOW';
            document.getElementById('pin2state').style.display = 'block';
            document.getElementById('pin2mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin2').textContent = getPinState(2) ? 'HIGH' : 'LOW';
            document.getElementById('pin2').style.display = 'block';
            document.getElementById('pin2state').style.display = 'none';
            document.getElementById('pin2mode').textContent = 'OUTPUT';
        }
        configPinMode(2, document.getElementById('pin2mode').textContent);
    });
    document.getElementById('pin3mode').addEventListener('click', function() {
        if (document.getElementById('pin3mode').textContent == 'OUTPUT') {
            document.getElementById('pin3').style.display = 'none';
            document.getElementById('pin3state').textContent = getPinState(3) ? 'HIGH' : 'LOW';
            document.getElementById('pin3state').style.display = 'block';
            document.getElementById('pin3mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin3').textContent = getPinState(3) ? 'HIGH' : 'LOW';
            document.getElementById('pin3').style.display = 'block';
            document.getElementById('pin3state').style.display = 'none';
            document.getElementById('pin3mode').textContent = 'OUTPUT';
        }
        configPinMode(3, document.getElementById('pin3mode').textContent);
    });
    document.getElementById('pin4mode').addEventListener('click', function() {
        if (document.getElementById('pin4mode').textContent == 'OUTPUT') {
            document.getElementById('pin4').style.display = 'none';
            document.getElementById('pin4state').textContent = getPinState(4) ? 'HIGH' : 'LOW';
            document.getElementById('pin4state').style.display = 'block';
            document.getElementById('pin4mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin4').textContent = getPinState(4) ? 'HIGH' : 'LOW';
            document.getElementById('pin4').style.display = 'block';
            document.getElementById('pin4state').style.display = 'none';
            document.getElementById('pin4mode').textContent = 'OUTPUT';
        }
        configPinMode(4, document.getElementById('pin4mode').textContent);
    });
    document.getElementById('pin5mode').addEventListener('click', function() {
        if (document.getElementById('pin5mode').textContent == 'OUTPUT') {
            document.getElementById('pin5').style.display = 'none';
            document.getElementById('pin5state').textContent = getPinState(5) ? 'HIGH' : 'LOW';
            document.getElementById('pin5state').style.display = 'block';
            document.getElementById('pin5mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin5').textContent = getPinState(5) ? 'HIGH' : 'LOW';
            document.getElementById('pin5').style.display = 'block';
            document.getElementById('pin5state').style.display = 'none';
            document.getElementById('pin5mode').textContent = 'OUTPUT';
        }
        configPinMode(5, document.getElementById('pin5mode').textContent);
    });
    document.getElementById('pin6mode').addEventListener('click', function() {
        if (document.getElementById('pin6mode').textContent == 'OUTPUT') {
            document.getElementById('pin6').style.display = 'none';
            document.getElementById('pin6state').textContent = getPinState(6) ? 'HIGH' : 'LOW';
            document.getElementById('pin6state').style.display = 'block';
            document.getElementById('pin6mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin6').textContent = getPinState(6) ? 'HIGH' : 'LOW';
            document.getElementById('pin6').style.display = 'block';
            document.getElementById('pin6state').style.display = 'none';
            document.getElementById('pin6mode').textContent = 'OUTPUT';
        }
        configPinMode(6, document.getElementById('pin6mode').textContent);
    });
    document.getElementById('pin7mode').addEventListener('click', function() {
        if (document.getElementById('pin7mode').textContent == 'OUTPUT') {
            document.getElementById('pin7').style.display = 'none';
            document.getElementById('pin7state').textContent = getPinState(7) ? 'HIGH' : 'LOW';
            document.getElementById('pin7state').style.display = 'block';
            document.getElementById('pin7mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin7').textContent = getPinState(7) ? 'HIGH' : 'LOW';
            document.getElementById('pin7').style.display = 'block';
            document.getElementById('pin7state').style.display = 'none';
            document.getElementById('pin7mode').textContent = 'OUTPUT';
        }
        configPinMode(7, document.getElementById('pin7mode').textContent);
    });
    document.getElementById('pin8mode').addEventListener('click', function() {
        if (document.getElementById('pin8mode').textContent == 'OUTPUT') {
            document.getElementById('pin8').style.display = 'none';
            document.getElementById('pin8state').textContent = getPinState(8) ? 'HIGH' : 'LOW';
            document.getElementById('pin8state').style.display = 'block';
            document.getElementById('pin8mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin8').textContent = getPinState(8) ? 'HIGH' : 'LOW';
            document.getElementById('pin8').style.display = 'block';
            document.getElementById('pin8state').style.display = 'none';
            document.getElementById('pin8mode').textContent = 'OUTPUT';
        }
        configPinMode(8, document.getElementById('pin8mode').textContent);
    });
    document.getElementById('pin9mode').addEventListener('click', function() {
        if (document.getElementById('pin9mode').textContent == 'OUTPUT') {
            document.getElementById('pin9').style.display = 'none';
            document.getElementById('pin9state').textContent = getPinState(9) ? 'HIGH' : 'LOW';
            document.getElementById('pin9state').style.display = 'block';
            document.getElementById('pin9mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin9').textContent = getPinState(9) ? 'HIGH' : 'LOW';
            document.getElementById('pin9').style.display = 'block';
            document.getElementById('pin9state').style.display = 'none';
            document.getElementById('pin9mode').textContent = 'OUTPUT';
        }
        configPinMode(9, document.getElementById('pin9mode').textContent);
    });
    document.getElementById('pin10mode').addEventListener('click', function() {
        if (document.getElementById('pin10mode').textContent == 'OUTPUT') {
            document.getElementById('pin10').style.display = 'none';
            document.getElementById('pin10state').textContent = getPinState(10) ? 'HIGH' : 'LOW';
            document.getElementById('pin10state').style.display = 'block';
            document.getElementById('pin10mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin10').textContent = getPinState(10) ? 'HIGH' : 'LOW';
            document.getElementById('pin10').style.display = 'block';
            document.getElementById('pin10state').style.display = 'none';
            document.getElementById('pin10mode').textContent = 'OUTPUT';
        }
        configPinMode(10, document.getElementById('pin10mode').textContent);
    });
    document.getElementById('pin11mode').addEventListener('click', function() {
        if (document.getElementById('pin11mode').textContent == 'OUTPUT') {
            document.getElementById('pin11').style.display = 'none';
            document.getElementById('pin11state').textContent = getPinState(11) ? 'HIGH' : 'LOW';
            document.getElementById('pin11state').style.display = 'block';
            document.getElementById('pin11mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin11').textContent = getPinState(11) ? 'HIGH' : 'LOW';
            document.getElementById('pin11').style.display = 'block';
            document.getElementById('pin11state').style.display = 'none';
            document.getElementById('pin11mode').textContent = 'OUTPUT';
        }
        configPinMode(11, document.getElementById('pin11mode').textContent);
    });
    document.getElementById('pin12mode').addEventListener('click', function() {
        if (document.getElementById('pin12mode').textContent == 'OUTPUT') {
            document.getElementById('pin12').style.display = 'none';
            document.getElementById('pin12state').textContent = getPinState(12) ? 'HIGH' : 'LOW';
            document.getElementById('pin12state').style.display = 'block';
            document.getElementById('pin12mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin12').textContent = getPinState(12) ? 'HIGH' : 'LOW';
            document.getElementById('pin12').style.display = 'block';
            document.getElementById('pin12state').style.display = 'none';
            document.getElementById('pin12mode').textContent = 'OUTPUT';
        }
        configPinMode(12, document.getElementById('pin12mode').textContent);
    });
    document.getElementById('pin13mode').addEventListener('click', function() {
        if (document.getElementById('pin13mode').textContent == 'OUTPUT') {
            document.getElementById('pin13').style.display = 'none';
            document.getElementById('pin13state').textContent = getPinState(13) ? 'HIGH' : 'LOW';
            document.getElementById('pin13state').style.display = 'block';
            document.getElementById('pin13mode').textContent = 'INPUT';
        }
        else {
            document.getElementById('pin13').textContent = getPinState(13) ? 'HIGH' : 'LOW';
            document.getElementById('pin13').style.display = 'block';
            document.getElementById('pin13state').style.display = 'none';
            document.getElementById('pin13mode').textContent = 'OUTPUT';
        }
        configPinMode(13, document.getElementById('pin13mode').textContent);
    });

}