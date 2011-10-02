init -> creates a new repository (you don't have to do this since I made one)

clone -> do this one. When it asks you for the path to your repositories, you should type:
/afs/ir.stanford.edu/users/p/c/pcostell/git

Then it will ask you to create a branch name. I try and do like branch per feature.

When using it, there are two main functions:

sync: downloads any changes on the server
upload: uploads your changes. It may ask you to run sync first if it decides that there is a conflict
branch: create a new branch or switch between branches.

Before you can do any of these commands, you must first

commit: This will commit any changes you have made to your local repo.

In order to commit, you have to:

add: do this for any files that you are working on. When you commit it should give you a little warning if there are files that you haven't added yet.

If you want a shortcut you can just say commit -a and it will automatically add everything for you.
