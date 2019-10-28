var net = require('net');

var stdin = process.openStdin();
/*


// Set input character encoding.

// Prompt user to input data in console.
console.log("Please input text in command line.");

// When user input data and click enter key.
standard_input.on('data', function (data) {

    // User input exit.
    if(data === 'exit\n'){
        // Program exit.
        console.log("User input complete, program exit.");
        process.exit();
    }else
    {
        // Print user input in console.
        console.log('User Input Data : ' + data);
    }
});

*/
var x = {
    user: 'david',
    pass: 'lol'
}
var client = new net.Socket();
// const readline = require('readline');


// client.connect(27015, '127.0.0.1', function () {
//     console.log('Connected');


// });
// console.log(JSON.stringify({
//     username: 'david',
// }))

// client.on('close', function () {
//     console.log('Connection closed');
// });


// // client.write(JSON.stringify({
// //     username:'david',
// // }));


// const rl = readline.createInterface({
//     input: process.stdin,
//     output: process.stdout
// });


client.on('data', function (data) {
    console.log('Received: ' + data);
    //client.destroy(); // kill client after server's response
});


function HDBSetup() {
    client.connect(27015, '127.0.0.1', function () {
        console.log('Connected');

        client.on('close', function () {
            console.log('Connection closed');
        });


        client.on('data', function (data) {
            console.log('Received: ' + data);
            //client.destroy(); // kill client after server's response
        });



    });
}



// while (true) {
//     rl.question('$> ', (answer) => {
//         // TODO: Log the answer in a database
//         client.write(answer.toString().trim());
//     });

// }

// stdin.addListener("data", function(d){
//    // console.log('you entered: '+d.toString().trim());
//     client.write(d.toString().trim())
// })





