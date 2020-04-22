#include <iostream>
#include <string>
#include <cassert>



// boost introduced a singly linked list whichh reduces runtime overhead
namespace contr = boost::container;
namespace fs  = boost::filesystem;

int main(int argc, char **argv)
{
	const std::string dir_name = argv[1];
	std::cout << dir_name << std::endl;
	contr::slist<std::string> playlist;

	try
	{
        // adding elements after
	contr::slist<std::string>::iterator  last = playlist.before_begin();
	/*
	 * later we will use
	 * playlist.emplace_after(last, item);
	 * ++last;
	 * */
         if(!fs::exists(dir_name) || !fs::is_directory(dir_name))
		 return 1;
	 fs::directory_iterator dirit(dir_name),end;
        
	 std::for_each(dirit , end , [playlist,last](const fs::directory_entry& entry)mutable{ 
			
			 playlist.emplace_after(last,entry.path().string());
			 ++last;

			 });
	}
	 catch(std::exception& e)
	 {
		 std::cout << "Exception Thrown: " << e.what() << std::endl;
	 }
	 std::cout << "---Boost List---" << std::endl;
	 BOOST_FOREACH(auto item, playlist)
	 {
		 std::cout << item << std::endl;
	 }	 
	return 0;
}
