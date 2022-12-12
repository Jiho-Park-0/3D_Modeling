module.exports = {
    HTML:function(title, list){
      return `
      <!doctype html>
      <html>
      <head>
        <meta charset="utf-8">
        <style>
        #text_group{
          width: 500px;
          margin: auto;
        }
        #text{
            width: fit-content;
            margin: auto;
            margin-right: 45px;
        }
        #btn_group{
                width: 500px;
                margin: auto;
            }
            #list{
              border: 1px solid darkcyan;
              background-color: rgba(0,0,0,0);
              color: darkcyan;
              padding: 5px;
              width: 100px;
              height: 30px;;
              margin: 10px;
              border-top-left-radius: 5px;
              border-top-right-radius: 5px;
              border-bottom-left-radius: 5px;
              border-bottom-right-radius: 5px;   
              margin-top: 30px;        
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
      </head>
      <body>
      <div id="text_group">
      <h1 id="text">Sparraw Becomes Pigeon</h1>
  </div>
  <div id="btn_group">
        ${list}
        </div>
        <div id="default">
            <button id="default_btn" onclick = "window.location='/default'" >Back to Main</button>
        </div>
      </body>
      </html>
      `;
    },list:function(filelist){
      var list = '<ul>';
      var i = 0;
      while(i < filelist.length){
        list = list + `<button id="list" target="_blank" onclick = "window.location='/modeling/${filelist[i]}'">${filelist[i]}</button>`
        i = i + 1;
      }
      list = list+'</ul>';
      return list;
    }
  }
  