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

function registerSchema(_schema) {
    client.write(JSON.stringify({schema:_schema, protocol:99}));
}


function addEntry(rowNumber, value) {
    client.write(JSON.stringify({ index: rowNumber, val: value, protocol: 100 }));
}

function addEntryCheckDup(rowNumber, value) {
    client.write(JSON.stringify({ index: rowNumber, val: value, protocol: 102 }));
}

function findAll(rowNumber, partialSearchValue) {
    client.write(JSON.stringify({ index: rowNumber, clue: partialSearchValue, protocol: 200 }));
}

function findOne(rowNumber, partialSearchValue) {
    client.write(JSON.stringify({ index: rowNumber, clue: partialSearchValue, protocol: 201 }));
}



function deleteEntry(rowNumber, partialSearchValue) {
    client.write(JSON.stringify({ index: rowNumber, clue: partialSearchValue, protocol: 402 }));
}

//add the modify stuff

function findOneAndUpdate(rowNumber, partialSearchValue){
    client.write(JSON.stringify({ index: rowNumber, clue: partialSearchValue, protocol: 301 }));
}

function findAllAndUpdate(){
    client.write(JSON.stringify({ index: rowNumber, clue: partialSearchValue, protocol: 300 }));
}