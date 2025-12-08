/*
 * Given a stream of product ID ranges, compute the sum of all invalid IDs
 *
 * product ID range are separated by a hyphen (e.g. 11-22), ranges are comma separated
 *
 * IDs are invalid if they are made up of sequences repeated twice.
 * E.g. 6464 (64 twice), 1188511885 (11885 twice)
 *
 * Strategy
 * 1.) Brute force
 *  - For each range given, iterate from start to end,
 *  - If first half of the numeric digits equal second half, then we have an invalid ID
 *  - To determine if first half of numeric digits equal to second half:
 *      - Convert to string, make sure even length number, compare first half to second half
 *      - Or we can identify the correct place to modulo
 *
 */

 #include<iostream>
 #include<vector>
 #include<string>


void processRangeString(std::vector<std::string>& ranges, std::string input, std::string del){
    // Given a string of comma separated ranges, split it up and store it in ranges vector
    size_t pos {0};
    while ((pos = input.find(del) )!= std::string::npos){
        ranges.push_back(input.substr(0, pos));
        input.erase(0, pos + del.length());
    }
    ranges.push_back(input);
    return;
}

 long long solve(std::vector<std::string>& ranges, std::string del){
     // Given a vector of ranges, find the sum of invalid IDs across these ranges
     long long res {0};
     size_t pos{0};

     for (int i=0; i< ranges.size(); i++){
         std::string range = ranges[i];
         pos = range.find(del);
         long long start = std::stoll(range.substr(0,pos));
         range.erase(0, pos+del.length());
         long long end = std::stoll(range);

         for (long long currNum=start; currNum <= end; currNum++){
             std::string currNumStr = std::to_string(currNum);
             if (currNumStr.length() % 2 == 0){
                 long long length = currNumStr.length() / 2;
                 if (currNumStr.substr(0, length) == currNumStr.substr(0+length, length)){
                     res += currNum;
                 }
             }
         }
     }

     return res;
 }

 int main(){
     long long res{0};
     std::vector<std::string> ranges;
     std::string input;
     std::cin >> input;

     processRangeString(ranges, input, ",");

     res = solve(ranges, "-");
     std::cout << res << std::endl;

     return 0;
 }
