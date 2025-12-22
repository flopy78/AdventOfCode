let read file_name =
  let input = open_in file_name in
  let rec read_lines () =
    try
      let line = input_line input in
      let lines,size = read_lines () in
      (line::lines,size+1)
    with
    |End_of_file -> ([],0)
  in
  let reversed_lines_list, size = read_lines () in
  let op_string, lines_list = 
    match List.rev reversed_lines_list with
    |[] -> failwith "invalid reading input"
    |head::tail->head, tail
  in
  let lines_array = Array.make_matrix (size-1) (String.length op_string) "" in
  List.iteri (
    fun row line -> 
      String.iteri (
        fun col char ->
          if char <> ' ' then
            lines_array.(row).(col) <- String.make 1 char
      ) line;
  ) lines_list;
  close_in input;
  op_string,lines_array








let main () =
  let op_string, lines = read "input.txt" in

  let answer = ref 0 in
  let local_answer = ref 0 in
  let current_op = ref ' ' in
  for i = 0 to String.length op_string - 1 do
    if op_string.[i] <> ' ' then begin
      current_op := op_string.[i];
      answer := !answer + !local_answer;
      local_answer := if !current_op = '+' then 0 else 1
    end;
    let str_number = String.concat "" (List.rev (List.init (Array.length lines) (fun j -> lines.(j).(i)))) in
    print_string str_number;
    print_newline ();
    if str_number <> "" then begin
      let number = int_of_string str_number; in
      if !current_op = '+' then
        local_answer := !local_answer + number
      else 
        local_answer := !local_answer * number 
    end
  done;
  answer := !answer + !local_answer;
  print_int !answer;
  print_newline ()

let () = main ()



  