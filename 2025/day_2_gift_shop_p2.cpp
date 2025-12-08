/*
 * Given a stream of product ID ranges, compute the sum of all invalid IDs
 *
 * product ID range are separated by a hyphen (e.g. 11-22), ranges are comma separated
 *
 * IDs are invalid if they are made up of sequences repeated at least twice.
 * E.g. 6464 (64 twice), 1188511885 (11885 twice), 95-115 (99 (9 twice), 111 (1 thrice))
 *
 * Strategy
 * 1.) Brute force
 *  - For each range given, iterate from start to end,
 *  - for each number from start to end, determine for up to the first half of the number if there is
 *  - a repeating sequence.
 *  - e.g. 646464
 *      - try first sequence 6
 *      - try next sequence 64 - found, add 646464 to the result
 *  - What do we mean by try?
 *      -  if we take the sequence and repeat itself until we reach the desired length, it must equal to the
 *      - "original" number
 *
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

std::string repeatString(std::string s, long long n){
    std::string repeat;
    for (long long i=0; i<n; i++){
        repeat += s;
    }
    return repeat;
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
             long long length = currNumStr.length();
             // initial sequence
             std::string seq = currNumStr.substr(0,1);
             long long seqEndPos {0};
             while (seq.length() <= length/2){
                 std::string repeatedSeq = repeatString(seq, length/seq.length());
                 if (repeatedSeq == currNumStr){
                     res += currNum;
                     break;
                 }
                 seqEndPos++;
                 seq += currNumStr[seqEndPos];
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
