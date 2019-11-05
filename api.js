var net = require('net');
var client = new net.Socket();

function connectClient() {
    client.connect(27015, '127.0.0.1', function () {
        console.log('Connected');

    });
    
}

function setupClient() {
    client.connect(27015, '127.0.0.1', function () {
        console.log('Connected');

    });

    client.on('data', function (data) {
        console.log('Received: ' + data + '-');
        //client.destroy(); // kill client after server's response
    });
}

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
            console.log('Received: ' + data + '-');
            //client.destroy(); // kill client after server's response
        });
    }


}

var person = {
    name:"David",
    pswd:"password",
    blood_group:"B",
    phoneNo:"9999999999",
    donorName: "John",
    donorFather: "Jack",
    transferDate: "22Jan2000",
    age: 22,
    sex: 'M',
}

var person2 = {
    name:"DavidVelho",
    pswd:"password",
    blood_group:"B",
    phoneNo:"9999999999",
    donorName: "John",
    donorFather: "Jack",
    transferDate: "22Jan2000",
    age: 22,
    sex: 'M',
}

function readFromDisk() {
    client.write(JSON.stringify({ protocol: -1 }));
}

function commit() {
    client.write(JSON.stringify({ protocol: 0 }));
}

function addEntry(value) {
    client.write(JSON.stringify({ val: value, protocol: 100 }));
}

function addEntryCheckDup(value) {
    client.write(JSON.stringify({ val: value, protocol: 102 }));
}

function findAll(phoneNo) {
    client.write(JSON.stringify({ val: phoneNo, protocol: 200 }));
}

function findOne(phoneNo) {
    client.write(JSON.stringify({ val: phoneNo, protocol: 201 }));
}

function deleteEntry(phoneNo) {
    client.write(JSON.stringify({ val: phoneNo, protocol: 402 }));
}

//add the modify stuff

function findOneAndUpdate(phoneNo, newData) {
    client.write(JSON.stringify({ val: { phoneNo: phoneNo, data: newData }, protocol: 301 }));
}

function findAllAndUpdate(phoneNo, newData) {
    client.write(JSON.stringify({ val: { phoneNo: phoneNo, data: newData }, protocol: 300 }));
}
