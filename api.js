var net = require('net');
var client = new net.Socket();

module.exports = {


    HDBSetup: function () {
        client.connect(27015, '127.0.0.1', function () {
            console.log('Connected');

        });
        client.on('close', function () {
            console.log('Connection closed');
            client.destroy();
        });
        client.on('data', function (data) {
            console.log('Received: ' + data);
            //client.destroy(); // kill client after server's response
        });
    }


}

function addEntry( value) {
    client.write(JSON.stringify({ val: value, protocol: 100 }));
}

function addEntryCheckDup( value) {
    client.write(JSON.stringify({ val: value, protocol: 102 }));
}

function findAll( phoneNo) {
    client.write(JSON.stringify({clue: phoneNo, protocol: 200 }));
}

function findOne(phoneNo) {
    client.write(JSON.stringify({  clue: phoneNo, protocol: 201 }));
}



function deleteEntry(phoneNo) {
    client.write(JSON.stringify({clue: phoneNo, protocol: 402 }));
}

//add the modify stuff

function findOneAndUpdate(phoneNo){
    client.write(JSON.stringify({ clue: phoneNo, protocol: 301 }));
}

function findAllAndUpdate(phoneNo){
    client.write(JSON.stringify({ clue: phoneNo, protocol: 300 }));
}