#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define CREATEBUCKET		1
#define INITIALIZEBUCKET	2
#define GETBUCKETINFO		3
#define PUTOBJECT		4
#define GETOBJECT		5
#define DELOBJECT		6

#define MAX_KV_KEY_SIZE		16
#define __NR_csd		555

struct demo_object {
	char country[256];
	int population;
};

struct csd_params {
	char compress;
	int key_len;
	int func_id;
	char *key;
	char *bucketID;
	char *msg;
	struct demo_object value;
} params;

void createbucket()
{
	if(!syscall(__NR_csd, &params)) {
		printf("OEI: Bucket created\n");
	} else {
		printf("OEI: Bucket create failed\n");
	}

	return;
}

void initializebucket()
{
	if(!syscall(__NR_csd, &params)) {
		printf("OEI: Bucket-> %s initialized\n", params.bucketID);
	} else {
		printf("OEI: Bucket-> %s initialization error\n", params.bucketID);
	}

	return;
}

void getbucketinfo()
{
	char bucketinfo[256];

	params.msg = bucketinfo;

	if(!syscall(__NR_csd, &params)) {
		printf("OEI: Success geting info of bucket %s\n", params.bucketID);
		printf("\nBucket Info: %s\n", bucketinfo);
	} else {
		printf("OEI: Error geting info of bucket %s\n", params.bucketID);
	}

	return;
}

void putobject()
{

	if(!syscall(__NR_csd, &params)) {
		printf("OEI: Success puting object in bucket %s\n", params.bucketID);
	} else {
		printf("OEI: Error puting object in bucket %s\n", params.bucketID);
	}

	return;
}

void getobject()
{

	if(!syscall(__NR_csd, &params)) {
		printf("OEI: Success puting object in bucket %s\n", params.bucketID);
	} else {
		printf("OEI: Error puting object in bucket %s\n", params.bucketID);
	}

	return;
}

void delobject()
{

	if(!syscall(__NR_csd, &params)) {
		printf("OEI: Success deleting object in bucket %s\n", params.bucketID);
	} else {
		printf("OEI: Error deleting object in bucket %s\n", params.bucketID);
	}

	return;
}

int main(int argc, char **argv)
{
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'f':
					params.func_id = atoi(argv[++i]);
					break;
				case 'b':
					params.bucketID = argv[++i];
					break;
				case 'l':
					params.key_len = atoi(argv[++i]);
					break;
				case 'k':
					params.key = argv[++i];
					break;
				case 'c':
					params.compress = argv[++i][0] == 'y';
					break;
				case 'v':
					strncpy(params.value.country, argv[++i], sizeof(params.value.country));
					params.value.population = atoi(argv[++i]);
					break;
				case 'h':
					printf("Usage:\n"
							"Description\n"
							"-f  func_id [1-6]\n"
							"-b  bucketID [String]\n"
							"-l  key_len [Integer]\n"
							"-k  key [String]\n"
							"-c  compress [y/n]\n"
							"-v  value object [String, Integer]\n"
                            "-h  help");
					return 0;
				default:
					break;
			}
		}
	}

	switch (params.func_id) {

		case CREATEBUCKET:
			createbucket();
			break;
		case INITIALIZEBUCKET:
			initializebucket();
			break;
		case GETBUCKETINFO:
			getbucketinfo();
			break;
		case PUTOBJECT:
			putobject();
			break;
		case GETOBJECT:
			getobject();
			break;
		case DELOBJECT:
			delobject();
			break;
		default:
			printf("Please enter a valid option.\n");
			break;
	}

	return 0;
}
