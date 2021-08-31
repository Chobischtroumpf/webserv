// Instantiating new EasyHTTP class
const http = new DeleteHTTP;

// Update Post
http.delete('http://127.0.0.1:8080/delete/example.html')

// Resolving promise for response data
.then(data => console.log(data))

// Resolving promise for error
.catch(err => console.log(err));
