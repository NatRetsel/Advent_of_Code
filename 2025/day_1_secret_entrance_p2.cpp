/*
 * We have a dial with numbers 0 to 99, one arrow initially pointed at number 50.
 * We are given instructions on how to spin the dial, L80 will mean to turn the dial left for 80 clicks,
 * one click for a number.
 *
 * Find the number of times the arrow hits 0
 *
 * Strategy
 * - Simulation
 *  - Iterate the combinations, for each combination, note the number of times it touches zero, including multi loops
 *
 * Note: After inputting dial instructions, terminate loop by entering any character.
 *
 *
 *
 */

 #include <cctype>
 #include<string>
 #include<iostream>

 int solve(){
     int currNum {50};
     std::string instruction {"L30"};
     int turnAmt {0};
     int completeLoops {0};
     int res {0};

     do {
         std::cin >> instruction;
         if (instruction[0] != 'L' && instruction[0] != 'R') break;
         for (int i=1; i<instruction.size(); i++) if (!std::isdigit(instruction[i])) break;
         completeLoops = std::stoi(instruction.substr(1,instruction.size()-1))/100;
         turnAmt = std::stoi(instruction.substr(1,instruction.size()-1))%100;

         if (instruction[0] == 'L'){
             if (currNum == 0) res--;
             currNum = currNum - turnAmt;
             if (currNum <= 0) {
                 res++;
                 if (currNum < 0) currNum += 100;
             }
         }else{
             currNum = currNum + turnAmt;
             if (currNum > 99){
                 currNum -= 100;
                 res++;
             }
         }

         res += completeLoops;
         //std::cout<<"Instruction: "<<instruction<<", loops: "<<completeLoops <<", turnAmt: "<<turnAmt<<
         //", currNum: "<<currNum<<", res: "<<res<<std::endl;
         //std::cout << "res: "<<res <<std::endl;
     }while (instruction.size() >= 2);

     return res;
 }

 int main(){
     int res {solve()};
     std::cout<<res<<std::endl;
     return 0;
 }
