function getFilename(fullPath) {
    return fullPath.replace(/^.*[\\\/]/, '');
}

window.onload = function(){
    var default_btn = document.getElementById('default_btn');
    default_btn.addEventListener('click', function(){
        window.location='/default';
        
    })

    var Modeling_btn = document.getElementById('Modeling_btn');
    Modeling_btn.addEventListener('click', function(){
        window.location='/default/modeling';
        
    })
    
    
}



