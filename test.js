// var net = require('net');

// var stdin = process.openStdin();

// class MyDB {

//     constructor(_username, _password, _ipaddr, _portno) {
        
//         this.username = _username;
//         this.password = _password;
//         this.portno = _portno;
//         this.ipaddr = _ipaddr;
//         this.stdin = process.openStdin();

//         this.client = new net.Socket();

//         this.client.connect(this.portno, this.ipaddr, function () {
//             console.log('Connected to ' + this.ipaddr + ' on port ' + this.portno);
//         });

//        this.client.on('data', function (data) {
    
    //             console.log('Received: ' + data);
    //             //client.destroy(); // kill client after server's response
    //         });
    //     }
    
    // }
    
    //var db = new MyDB('root', 'root', '27015', '127.0.0.1');


var net = require('net');
var stdin = process.openStdin();
var client = new net.Socket();
try {
    client.connect(27015, '127.0.0.1', function () {
        console.log('Connected');
    });

}
catch (e) {

}
stdin.addListener("data", function (d) {
    console.log('you entered: ' + d.toString().trim());
    client.write(d.toString().trim())
})



client.on('data', function (data) {

    console.log('Received: ' + data);
    //client.destroy(); // kill client after server's response
});


client.on('close', function() {
	console.log('Connection closed');
});

