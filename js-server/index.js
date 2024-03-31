const pinCount = 14;

async function updatePinStates() {
    for (let i = 0; i < pinCount; i++) {
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

    for (let i = 0; i < pinCount; i++) {
        document.getElementById('pin' + i).addEventListener('click', function() {
            if (document.getElementById('pin' + i + 'mode').textContent == 'OUTPUT') {
                setPinState(i, !getPinState(i));
                console.log('Pin ' + i + ' has the state ' + getPinState(i));
                document.getElementById('pin' + i).textContent = getPinState(i) ? 'HIGH' : 'LOW';
            }
        });

        document.getElementById('pin' + i + 'mode').addEventListener('click', function() {
            if (document.getElementById('pin' + i + 'mode').textContent == 'OUTPUT') {
                document.getElementById('pin' + i).style.display = 'none';
                document.getElementById('pin' + i + 'state').textContent = getPinState(i) ? 'HIGH' : 'LOW';
                document.getElementById('pin' + i + 'state').style.display = 'block';
                document.getElementById('pin' + i + 'mode').textContent = 'INPUT';
            }
            else {
                document.getElementById('pin' + i).textContent = getPinState(i) ? 'HIGH' : 'LOW';
                document.getElementById('pin' + i).style.display = 'block';
                document.getElementById('pin' + i + 'state').style.display = 'none';
                document.getElementById('pin' + i + 'mode').textContent = 'OUTPUT';
            }
            configPinMode(i, document.getElementById('pin' + i + 'mode').textContent);
        });
    }
}