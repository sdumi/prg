
Object.extend(String.English,{});Quiz=SC.Object.create({server:SC.Server.create({prefix:['Quiz']}),FIXTURES:[]});function main(){Quiz.server.preload(Quiz.FIXTURES);SC.page.awake();};require('core');Quiz.appController=SC.Object.create({message:"",message2:"",submit_quiz:function(){var msg=document.getElementById('my_text_area').value;var url="http://aww.trc.alcatel.ro/temp/sqlUpdate.php";url=url+"?text="+'"'+encodeURIComponent(msg)+'"';Quiz.appController.set('message2',msg.length+" "+url);new Ajax.Request(url,{method:'get',asynchronous:true,onSuccess:function(response){Quiz.appController.set('message2',"Thank you: quiz succesfully sent. Got another one?");document.getElementById('my_text_area').value="";},onFailure:function(){Quiz.appController.set('message2','failed to submit the message');}});},keyWatcher:function(){var msg=Quiz.appController.get('message2');if(msg.length>0){Quiz.appController.set('message2',"");}},normalize:function(str){result="";for(i=0;i<str.length;i++){switch(str.charCodeAt(i)){case 13:break;case 10:result+="____";break;default:result+=str.charAt(i);break;}}
return result;},test_quiz:function(){var text=Quiz.appController.get('message');Quiz.appController.set('message2',Quiz.appController.normalize(text));var url="http://aww.trc.alcatel.ro/temp/sqlUpdate.php";url=url+"?text="+'"'+Quiz.appController.normalize(Quiz.appController.get('message'))+'"';Quiz.appController.set('message2',url);Quiz.appController.set('message2',"length: "+text.length+" s[-2]: "+text.charCodeAt(text.length-2)+" s[-1]: "+text.charCodeAt(text.length-1)+""+url);}});