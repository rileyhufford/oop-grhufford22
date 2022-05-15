import { volleyball } from "./volleyball.mjs";

const myVolleyball = new volleyball("green", false, true);

console.assert(myVolleyball.color == "green", "Color failed");
console.assert(myVolleyball.professional == false, "Professional failed");
console.assert(myVolleyball.inflated == false, "Professional failed");
/*
//console.log(myVolleyball);
try { 
    console.assert(myVolleyball.color == "green", "Color failed");
    console.log("Color passed");
}
catch(error) { console.error("Color failed"); }

try { 
    console.assert(myVolleyball.professional == false); 
    console.log("Professional passed");
}
catch { console.log("Professional failed"); }

try { 
    console.assert(myVolleyball.inflated == true); 
    console.log("Inflated passed")
}
catch { console.log("Inflated failed"); }


//catch
//{
    //console.log("Color failed");
//}

//console.assert(myVolleyball.color == "green", "Color failed");
//console.log("Color passed"); //unreachable if assert fails
//console.assert(myVolleyball.professional == false, "Professional failed");
//console.log("Professional passed"); //unreachable if assert fails
//console.assert(myVolleyball.inflated == true, "Inflated failed");
//console.log("Inflated passed"); //unreachable if assert fails
*/