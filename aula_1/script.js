input = '{1,2,3,4},{1,2},{1,3},{2,3},{2,4},{3,4}'
sep = input.split(',')

// matriz (direcionado)
el_index = 0
target_node = ''
nodes = []
matrix = []
for (let el of sep){
    let end = false
    let str = el
    if(el.includes('{')){
       str = str.replace('{', '')
    }
    if(el.includes('}')){
       str = str.replace('}', '')
       end = true
    }
    if(el_index == 0){
        nodes.push(str)
        if(end){
            for(i=0;i<nodes.length;i++){
                matrix.push([])
                for(y=0;y<nodes.length;y++){
                    matrix[i].push(0)
                }
            }
        }
    }
    else{
        if(target_node == ''){
            target_node = str
        }
        else{
            matrix[nodes.indexOf(target_node)][nodes.indexOf(str)] = 1
            target_node = ''
        }
    }
    el_index += end
}
// matriz (n direcionado)
el_index = 0
target_node = ''
nodes = []
matrix = []
for (let el of sep){
    let end = false
    let str = el
    if(el.includes('{')){
       str = str.replace('{', '')
    }
    if(el.includes('}')){
       str = str.replace('}', '')
       end = true
    }
    if(el_index == 0){
        nodes.push(str)
        if(end){
            for(i=0;i<nodes.length;i++){
                matrix.push([])
                for(y=0;y<nodes.length;y++){
                    matrix[i].push(0)
                }
            }
        }
    }
    else{
        if(target_node == ''){
            target_node = str
        }
        else{
            matrix[nodes.indexOf(target_node)][nodes.indexOf(str)] = 1
            matrix[nodes.indexOf(str)][nodes.indexOf(target_node)] = 1
            target_node = ''
        }
    }
    el_index += end
}

// lista (direcionado)
el_index = 0
target_node = ''
nodes = []
for (let el of sep){
    let end = false
    let str = el
    if(el.includes('{')){
       str = str.replace('{', '')
    }
    if(el.includes('}')){
       str = str.replace('}', '')
       end = true
    }
    if(el_index == 0){
        nodes.push({'name':str, 'rel':[]})
    }
    else{
        if(target_node == ''){
            target_node = str
        }
        else{
            nodes.find(n => n.name == target_node).rel.push(str)
            target_node = ''
        }
    }
    el_index += end
}
// lista (não direcionado)
el_index = 0
target_node = ''
nodes = []
for (let el of sep){
    let end = false
    let str = el
    if(el.includes('{')){
       str = str.replace('{', '')
    }
    if(el.includes('}')){
       str = str.replace('}', '')
       end = true
    }
    if(el_index == 0){
        nodes.push({'name':str, 'rel':[]})
    }
    else{
        if(target_node == ''){
            target_node = str
        }
        else{
            nodes.find(n => n.name == target_node).rel.push(str)
            nodes.find(n => n.name == str).rel.push(target_node)
            target_node = ''
        }
    }
    el_index += end
}