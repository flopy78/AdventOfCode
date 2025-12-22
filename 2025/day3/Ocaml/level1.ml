let read file_name =
    let input = open_in file_name in
    let rec read_lines () =
      try
        let line = input_line input in
          line::read_lines ()
      with
      |End_of_file->[]
    in 
    let parsed = read_lines () in
    close_in input;
    parsed


let rec get_max_number string n_digits =
  if n_digits = 0 then
     ""
  else begin
    let max_char_idx = ref 0 in
    let max_char = ref '0' in
    for i = 0 to (String.length string - n_digits) do
      if string.[i] > !max_char then begin
        max_char := string.[i];
        max_char_idx := i
      end  
    done;
    String.concat "" [String.make 1 !max_char ; get_max_number (String.sub string (!max_char_idx+1) (String.length string -(!max_char_idx+1))) (n_digits -1)]
  end

  
let main () =
      let input = read "input.txt" in
      let total = ref 0 in
      List.iter (
        fun string -> 
        total := !total + int_of_string (get_max_number string 2)
    ) input;
    print_int !total;
    print_newline ()
    
let () = main ()