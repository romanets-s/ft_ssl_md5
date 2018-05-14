#include "md5.h"

int	main(void){
	t_md5				*hash;
	
	hash = init_ft_md5("", 0);
	ft_md5(hash, -1);
	return (0);
}