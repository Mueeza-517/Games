let boxes = document.querySelectorAll(".box");
let resetbutton = document.querySelector(".Reset-btn");
let gameOver = false;

let filledBoxes = 0;
let turn = true;

const winPatterns = [
    [0, 1, 2], 
    [3, 4, 5], 
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7], 
    [2, 5, 8],
    [0, 4, 8], 
    [2, 4, 6]
];

boxes.forEach((box) =>{
    box.addEventListener('click',() =>{
       if(box.innerText != " ")
        filledBoxes++;
        console.log(filledBoxes)
        if(turn){
            box.innerText = "⭕";
            turn = false;
        } else {
            box.innerText ="❌";
            turn = true;
        }
        box.disabled = true;
        checkWinner();
    });
});


const checkWinner = () =>{
  for(pattern of winPatterns){ 
   let position1 = boxes[pattern[0]].innerText;
   let position2 = boxes[pattern[1]].innerText;
   let position3 = boxes[pattern[2]].innerText;

   if(position1 != "" && position2 != "", position3 != ""){
    if(position1 == position2 && position2 == position3){
          showPopup(`player ${position1} win`)
          disabledAllboxes()
        gameOver = true;
    }  else if(filledBoxes === 9 && !gameOver){
     showPopup("It's a draw 😐")
     disabledAllboxes()  
    }
   }
  }
} 

function disabledAllboxes(){
    boxes.forEach((box =>{
        box.disabled = true;
    }))
}

function enableAllboxes(){
    boxes.forEach((box =>{
        box.disabled = false;;
        box.innerText = " ";
    }))
}


function showPopup(message) {
  document.getElementById("msg").innerText = message;
  document.getElementById("popup").style.display = "block";
  setTimeout(hidePopup, 2500); // hide popup after 2 seconds
}

function hidePopup() {
  document.getElementById("popup").style.display = "none";
}

const resetGame = () =>{
  turn = true;
  enableAllboxes();
}

resetbutton.addEventListener("click" , resetGame);


/*  logic how the game is working
 we are using the 2D array in this

first og all for this we print the
all patterns console.log([pattern[0]], [pattern[1]], [pattern[3]])
console.log([boxes[pattern[0]]], [boxes[pattern[1]]], [boxes[pattern[3]]])

// is step my hm har box ko index dy rhy hain hm ye bhi kah sakty hain
 
// sab sy phly hmm ny ye check kya ky kis kis pattern pr winner
jeet sakta hai un sarry patterns ko winning patterns my store 
krwa dya hmmny us ky bad hmm ny ek loop chalai haijo hamin sab
ka paterrn btta rhi thius loop ny hamin sarry pattern btta dye 
jo hamri 2D array my store thyab hamin kya krna tha ye dekhna 
tha ky boxes pr wo patterns active bhi hain ya nhiphir hmm ny 
unhi patterns ko boxes pattern or phir index btta kr print krwaya 
ab hamain hr box btta raha tha ky kis array pr wo box hai mean to
say ksi point pr available hai iss tarah hmain ye bhi ptta chal gya
ky hm thk kam kr rhy hain us ky badd h, ny patten 0 ko ek alag variable 
my pattern 2 lo ky alag variable my or pattern 3 ko ek alag variable
my store krwa dya or phir ye check kya ky un boxes ki value empty tu
hi hai agr empty hai tu inner if nhi chaly ga us ky badd wo check kary
ga  ab patterns tu us ky pass hain sarry ab us ny check krna hai ky 
kya jo patterns hainun pr values same hai age same hai tu winner ka messag
e a jae ga pr agr koi bhi player win nhi kya tu draw ka message a jaye ga

note( agr phir bhi bhool jaye tu shrada khapra ka JavaScript ka lecture number 9 
dekh lena ap . ap ko revise hu jaye ga )
*/