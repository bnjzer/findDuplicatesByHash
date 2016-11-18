# findDuplicatesByHash

Program that finds duplicates in a directory recursively based on the hash of files (md5sum). It can also find duplicates recursively between 2 directories.  

To do that, it browses through the directory and builds a [trie](https://en.wikipedia.org/wiki/Trie) where the path of a leaf is the md5sum of the file. When adding a hash to the trie, if it's already there then the 2 paths are displayed.  

If the program is used with 2 directories, for each file of the second directory it just checks if its md5sum is in the trie.

## Usage

```bash
Usage: ./bin/findDuplicatesByHash <dir> [dir2]

  dir: browsed recursively to find duplicates
  dir2: if set, the program looks for duplicates between dir and dir2 recursively

  dir and dir2 must be directories
```

## Example

### With 1 directory

```bash
$ mkdir -p /tmp/dir/orange
$ for c in {a..m}; do echo $c$c$c$c$c$c$c$c > /tmp/dir/$c; done
$ cp /tmp/dir/a /tmp/dir/banana
$ cp /tmp/dir/l /tmp/dir/orange/apple
$ ./bin/findDuplicatesByHash /tmp/dir
/tmp/dir/banana
  /tmp/dir/a

/tmp/dir/l
  /tmp/dir/orange/apple
```

### With 2 directories

```bash
$ mkdir /tmp/{dir1,dir2}
$ for c in {a..m}; do echo $c$c$c$c$c$c$c$c > /tmp/dir1/$c; done
$ for c in {n..z}; do echo $c$c$c$c$c$c$c$c > /tmp/dir2/$c; done
$ ./bin/findDuplicatesByHash /tmp/dir1/ /tmp/dir2/
$ cp /tmp/dir1/a /tmp/dir2/pineapple
$ mkdir -p /tmp/dir2/apricot/
$ cp /tmp/dir1/l /tmp/dir2/apricot/lemon
$ ./bin/findDuplicatesByHash /tmp/dir1/ /tmp/dir2/
/tmp/dir1/a
  /tmp/dir2/pineapple

/tmp/dir1/l
  /tmp/dir2/apricot/lemon
```

## Limits

All the files contained in the directory (recursively) will be stored in the trie in RAM. Each node in the trie stores 37 pointers :
- 1 pointer to `char` so that the leaves can point to the path of the file it represents
- 26 (letters) + 10 (digits) = 36 pointers to another node (child) in order to build the tree
On a 64-bit machine a pointer is stored with 8 bytes, so a node requires 37 * 8 = 296 bytes of RAM.

Let's say the directory has 10 000 files, there needs 296 * 10 000 = 2.9 GB of RAM to store the trie (actually less because there will be some nodes in common in the trie but still).  

If there is a lot of files it will require a lot of time to compute all the hashes as well.  

We must be aware of that when using this program.  

When using it with 2 directories, the smartest thing to do is to pass the directoriy with the most files as the first argument.

## Requirements to compile

- Fedora : package `openssl-devel`
- Debian : package `libssl-dev` (not tested)

