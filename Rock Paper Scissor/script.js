let userScore = 0;
let compScore = 0;

let userIncrement = document.querySelector("#user-score");
let compIncrement = document.querySelector("#comp-score");
let msg = document.querySelector("#msg")
const boxes = document.querySelectorAll(".box")


const getCompChoice = () =>{
    const options = ["rock", "paper", "scissor"];
    const randomIndex = Math.floor(Math.random() * 3);
    return options[randomIndex];
     
}

const showWinner = (userWin, userChoice , compChoice) =>{
    if(userWin){
        console.log("userWin")
        userScore++;
        userIncrement.innerText = userScore
        msg.innerText = `You Win! your ${userChoice} beats ${compChoice} 🥳`;
    } else {
        console.log("CompWin")
        compScore++;
        compIncrement.innerText = compScore;
        msg.innerText = `you Lose ${compChoice} beats your ${userChoice}😔`
    }
}

const playGame = (userChoice) =>{
    console.log("user choice" , userChoice)
    const compChoice = getCompChoice();
     console.log("comp choice" , compChoice);

     if(userChoice == compChoice){
        console.log("It's a Draw");
        msg.innerText = "It's a Draw 😒"
     } else {
        let userWin = true;
        if( userChoice == "rock"){
            // comp choice = Scissor,paper 
            // (agr user choice rock ho gi tu ya tu compChoice scissor ho gi ya paper
            //  Q ky agr equal hota tu start my hi ptta chal jata is lye hmm rock ko consider 
            //  nhi karein gy ab us ky badd hm dekin gy ky rock ky against kon jety ga
            //  paper rock ky aginst jety ga tu wo false return kry ga or us ky elawa scissor 
            //  hu ga scissor or rock my rock jety ga)
            userWin = compChoice == "paper" ? false :  true;
        } else if (userChoice == "paper") {
            //comp choice= scissor,rock
            userWin = compChoice == "scissor" ? false : true;
        }  else {
          //comp choice == rock, paper
           userWin = compChoice == "rock" ? false : true;
        }
      showWinner(userWin ,userChoice , compChoice);
     }
 }


boxes.forEach((box) =>{
    box.addEventListener('click' ,() =>{
        const userChoice = box.getAttribute("id")
        playGame(userChoice)
    })
})

/* is game ki logic ye hai ky sab sy phly hmmny query selector my sy box ko get kya hai
ussy ek vairable my store kya hai or phir ussy variable pr for each loop laga di hai taky
one by one hamian ek ek box get hu jay . issi tarah hmm ny attribute ko bhi get kya hai
attribute my hmm ny user choice store krwaii hui hai us ka cpde indexhtml my likha hua hai
tu hmm ny play game ky name sy ek  function banaya hai jis my hmm ny user choice ko pass
kya hai ab hmm paly game ky function my atty hain us my sab sy phly tu hmm ny user choice ko
print krwaya hai console pr us ky baad ham computer ky sath kheer rhy hain hamain computer
choice ko bhi print krwana hai us ky lye hm ny computere choice ky name sy ek alag function
bana lya jis my hm ny ek variable banaya hai us my hmm ny ek array banai hai us my hmm ny
sab choices ko store krwaya hai rock , paper or scissor ko ab hmm chahty hain computer khely us
ky lye ek function hota hai math my random name sy jo hamin koi bhi random value generate
kr ky dy deta hai hamin 3 eandom vlaue generate krni hai tu ham ny ussy 3 sy muliply kya
hai ab hamain ptta hai function kuch return bhi krta hai tu hmm ny return my option or us 
ki array my jo hmm ny random function banaya tha ussy ek variable my store bhi krwaya tha
to return my hmm options or square braces laga kr randomIndex ka variable pass krwa dein gy*/