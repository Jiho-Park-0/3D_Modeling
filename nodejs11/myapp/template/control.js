module.exports = {
    HTML:function(cor){
      return `
      <!DOCTYPE html>
<html>
    <style>
    .group{
        width: 700px;
        margin: auto;
    }
    .group input[type="text"]{
        margin-top: 5%;
        width: 300px;
        text-align:center;
        height: 32px;
        font-size: 15px;
        border: 0;
        border-radius: 15px;
        outline: none;
        padding-left: 10px;
        background-color: rgb(233, 233, 233);
    }
    .group input[type="submit"]{
        border: 1px solid skyblue;
            background-color: rgba(0,0,0,0);
            color: skyblue;
            padding: 5px;
            width: 55px;
            height: 30px;
            border-top-left-radius: 5px;
            border-top-right-radius: 5px;
            border-bottom-left-radius: 5px;
            border-bottom-right-radius: 5px;   
            margin-top: 30px;
    }
        #text_group{
            width: 500px;
            margin: auto;
          }
          #text{
              width: fit-content;
              margin: auto;
              margin-right: 45px;
          }
          #coordinate_group{
            word-spacing: 2.2em;
            width: 500px;
            margin: auto;
          }
          #default{
            width: 150px;
            margin: auto;
          }
          button{
            border: 1px solid skyblue;
            background-color: rgba(0,0,0,0);
            color: skyblue;
            padding: 5px;
            width: 100px;
            height: 50px;;
            margin: 10px;
            border-top-left-radius: 5px;
            border-top-right-radius: 5px;
            border-bottom-left-radius: 5px;
            border-bottom-right-radius: 5px;   
            margin-top: 30px;        
          }
    </style>
    <body>
    <div id="text_group">
      <h1 id="text">Sparraw Becomes Pigeon</h1>
  </div>
  <div class="group">
        <form action="/default/control" method="post">
            <input control_x ="control_x" type="text" name="control_x" placeholder="control_x">
            <input control_y ="control_y" type="text" name="control_y" placeholder="control_y">
            <input type="submit" value="Submit">
        </form>
        </div>
        <div id="coordinate_group">
            ${cor}
        </div>
        <div id="default">
            <button id="default_btn" onclick = "window.location='/default'" >Back to Main</button>
        </div>
    </body>
</html>
      `;
    },Coordinates:function(x=0 ,y=0){
        var html = `
        <h1> x = ${x} &nbsp y = ${y} </h1>`
        ;
      return html;
    }
  }