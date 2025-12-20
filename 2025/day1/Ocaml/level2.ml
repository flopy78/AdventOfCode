(*Using a normal modulo*)
let (mod) x y = ((x mod y) + y) mod y;;

let read file_name =
    let file = open_in file_name in
    let rec read_lines () =
      try
        let line = input_line file in
        let direction = line.[0] in
        let number = int_of_string (String.sub line 1 (String.length line -1)) in
        (direction,number)::read_lines()
      with
      |End_of_file->[]
    in let result = read_lines() in
    close_in file;
    result
  
let rec simulate dial steps zero_counter =
    match steps with
    |[]->zero_counter
    |(direction,number)::tail->
      if direction = 'L' then begin
        let new_dial = (dial-number) mod 100 in
        let new_zero_counter = zero_counter + number/100 + if (new_dial = 0 || (new_dial > dial && dial <> 0)) then 1 else 0 in

        simulate new_dial tail new_zero_counter
      end 
      else begin 
        let new_dial = (dial+number) mod 100 in
        let new_zero_counter = zero_counter + number/100 + if (new_dial < dial) then 1 else 0 in

        simulate new_dial tail new_zero_counter  
      end






    
let main () = 
  let input = read "input.txt" in
    print_int (simulate 50 input 0);
    print_newline ()

let () = main ()