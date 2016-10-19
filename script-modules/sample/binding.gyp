
{
  "targets": [
    {
      "target_name": "sample",
      "sources": [ "sample.cpp", "myobject.cpp" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}