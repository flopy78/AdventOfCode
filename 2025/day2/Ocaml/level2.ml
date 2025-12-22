let read file_name =
    let parse_range range_string =
        let liste = String.split_on_char '-' range_string in
        match liste with 
        |low::[high]->(int_of_string low,int_of_string high)
        |_->failwith "invalid input"
    in
    let input = open_in file_name in
    let line = input_line input in
    let ranges_string = String.split_on_char ',' line in
    List.map parse_range ranges_string



let main () = 
  let is_invalid n =
     let string_n = string_of_int n in
     let size = String.length string_n in
     let answer = ref false in
     for size_block = 1 to size/2 do
        let valid_divisor = ref true in
        if size mod size_block = 0 then begin
          (*print_string "d ";
          print_int d;
          print_newline ();*)
          let n_blocks = size/size_block in
          let buffer = ref (String.sub string_n 0 (size_block)) in
          for j = 1 to n_blocks-1 do
            valid_divisor := !valid_divisor && (!buffer = String.sub string_n (j*size_block) size_block);
            buffer :=  String.sub string_n (j*size_block) size_block
          done;
          answer := !answer || !valid_divisor;
        end
      done;
      !answer
      
  in
  let ranges = read "input.txt" in
  let counter = ref 0 in
  List.iter (
    fun (low,high) ->
      for n = low to high do
        if is_invalid n  then begin
          counter := !counter + n;
        end
      done
  ) ranges;
  print_int !counter;
  print_newline ()
let () = main ()