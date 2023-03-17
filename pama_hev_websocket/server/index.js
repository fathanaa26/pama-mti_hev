const express = require("express");
const { createServer } = require("http");
const { Server } = require("socket.io");

const app = express();
const httpServer = createServer(app);
const io = new Server(httpServer, { /* options */ });

let i = 0;

io.on("connection", (socket) => {
  setInterval(()=>{
    socket.send(i++)
  },20)

  socket.on("event_name",(data)=>{
    console.log(data);
  })
});

httpServer.listen(3001,()=>{
  console.log("listening on 3001")
});