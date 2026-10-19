# 计算文件哈希,忽略所有空白与注释。用于核对代码誊抄是否正确。
cpp -dD -P -fpreprocessed | tr -d '[:space:]'| md5sum |cut -c-6
